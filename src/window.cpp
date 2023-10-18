// For now, the load_gl_function is inside the gl_renderer.hpp file,
// this will be changed in the future. This function must be defined in a
// helper/utility file for the opengl library.
#include "renderer/gl_renderer.hpp"

// ---
#include "utils/logger.hpp"

// Headers
#include "game.hpp"
#include "lib/opengl/wglext.h"
#include "window.hpp"

// Libs
// clang-format off
#include <stdio.h>
#include <iostream>
// clang-format on

namespace window {
  // OpenGL functions
  PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB       = nullptr;
  PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;

  /**
   * Window callback
   */
  LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = 0;

    switch(uMsg) {
      case WM_CLOSE: {
        game::running = false;
        break;
      }

      default: {
        result = DefWindowProcA(hwnd, uMsg, wParam, lParam);
        break;
      }
    }

    return result;
  }

  /**
   * Check if the window was already created.
   *
   * @return Whether or not the window was already created.
   */
  bool window_created() { return window::window != nullptr; }

  /**
   * Instantiating the window. This method will be called twice,
   * once to create a fake window to load the OpenGL functions,
   * and once to create the real window.
   *
   * @param width The width of the window.
   * @param height The height of the window.
   * @param title The title of the window.
   * @return Whether or not the window was created successfully.
   */
  bool instantiate_window(int width, int height, std::string title) {
    HINSTANCE hInstance = GetModuleHandleA(0);  // Get the current instance

    // The window classname
    LPCSTR window_classname = "CelesteWindow";

    int window_center_x = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
    int window_center_y = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

    if(window::window_created()) {
      // If we already have an instance of the window, we will create another one
      // since this call is probably to create the actual window.
      // clang-format off
      window::window = CreateWindowExA(
          0,
          window_classname, title.c_str(),
          window::window_style,
          window_center_x, window_center_y,
          width, height, 0, 0,
          hInstance,
          0
      );
      // clang-format on

      return !(!window::window);
    }

    // The window class
    WNDCLASSA wc     = {};
    wc.hInstance     = hInstance;
    wc.lpszClassName = window_classname;
    wc.hIcon         = LoadIcon(hInstance, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(0, IDC_ARROW);
    wc.lpfnWndProc   = window::window_callback;

    if(!RegisterClassA(&wc)) {
      MessageBoxA(0, "Failed to register window class.", "Error", MB_ICONERROR);
      return false;
    }

    // Create the fake window
    // clang-format off
    window::window = CreateWindowExA(
        0,
        window_classname, title.c_str(),
        window::window_style,
        window_center_x, window_center_y,
        width, height, 0, 0,
        hInstance,
        0
    );
    // clang-format on

    return !(!window::window);
  }

  /**
   * Init and setup the window OpenGL functions and return a pointer to it.
   *
   * @param hdc The pointer to the created device context.
   * @param pfd The pointer to the created pixel format descriptor.
   * @return Whether or not the OpenGL functions were loaded successfully.
   */
  bool init_window_gl_functions(HDC* hdc, PIXELFORMATDESCRIPTOR* pfd) {
    *hdc = GetDC(window::window);
    if(!*hdc) { return false; }

    pfd->nSize      = sizeof(PIXELFORMATDESCRIPTOR);
    pfd->nVersion   = 1;
    pfd->dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd->iPixelType = PFD_TYPE_RGBA;
    pfd->cColorBits = 32;
    pfd->cAlphaBits = 8;
    pfd->cDepthBits = 24;

    int pixel_format = ChoosePixelFormat(*hdc, pfd);
    if(!pixel_format) { return false; }

    if(!SetPixelFormat(*hdc, pixel_format, pfd)) { return false; }

    return true;
  }

  /**
   * Load the OpenGL functions.
   *
   * @return Whether or not the OpenGL functions were loaded successfully.
   */
  bool load_gl_functions() {
    // Load OpenGL functions
    wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)gl_renderer::load_gl_function("wglChoosePixelFormatARB");
    wglCreateContextAttribsARB =
        (PFNWGLCREATECONTEXTATTRIBSARBPROC)gl_renderer::load_gl_function("wglCreateContextAttribsARB");

    return (wglChoosePixelFormatARB && wglCreateContextAttribsARB);
  }

  /**
   * Main method to create a window.
   *
   * @param width The width of the window.
   * @param height The height of the window.
   * @param title The title of the window.
   */
  bool create_window(int width, int height, std::string title) {
    {
      // Create the fake window
      instantiate_window(width, height, title);

      HDC hdc                   = nullptr;
      PIXELFORMATDESCRIPTOR pfd = {};

      if(!init_window_gl_functions(&hdc, &pfd)) { return false; }

      HGLRC temp_context = wglCreateContext(hdc);
      if(!temp_context) { return false; }

      if(!wglMakeCurrent(hdc, temp_context)) { return false; }

      if(!load_gl_functions()) { return false; }

      // Clean up the temporary context
      wglMakeCurrent(hdc, 0);
      wglDeleteContext(temp_context);
      ReleaseDC(window::window, hdc);

      DestroyWindow(window::window);
    }

    // Create the real window
    {
      {
        RECT canvas = {};
        AdjustWindowRectEx(&canvas, window::window_style, 0, 0);

        width += canvas.right - canvas.left;
        height += canvas.bottom - canvas.top;
      }

      instantiate_window(width, height, title);

      HDC hdc = GetDC(window::window);
      if(!hdc) { return false; }

      // clang-format off
      const int pixel_attribs[] = {
        WGL_DRAW_TO_WINDOW_ARB,   GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB,   GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,    GL_TRUE,
        WGL_PIXEL_TYPE_ARB,       WGL_TYPE_RGBA_ARB,
        WGL_ACCELERATION_ARB,     WGL_FULL_ACCELERATION_ARB,
        WGL_COLOR_BITS_ARB,       32,
        WGL_ALPHA_BITS_ARB,       8,
        WGL_DEPTH_BITS_ARB,       24,
        WGL_STENCIL_BITS_ARB,     8,
        WGL_SAMPLE_BUFFERS_ARB,   GL_TRUE,
        WGL_SAMPLES_ARB,          4,
        0
      };
      // clang-format on

      UINT num_formats = 0;
      int pixel_format = 0;

      if(!wglChoosePixelFormatARB(hdc, pixel_attribs, 0, 1, &pixel_format, &num_formats)) {
        logger::log("Failed to choose pixel format.", "Error", logger::color::red);
        return false;
      }

      PIXELFORMATDESCRIPTOR pfd = {};
      DescribePixelFormat(hdc, pixel_format, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

      if(!SetPixelFormat(hdc, pixel_format, &pfd)) {
        logger::log("Failed to set pixel format.", "Error", logger::color::red);
        return false;
      }

      // clang-format off
      const int context_attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        //non-debug reasons:
        WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        //debug reasons:
        //WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_DEBUG_BIT_ARB,
        0
      };
      // clang-format on

      HGLRC gl_context = wglCreateContextAttribsARB(hdc, 0, context_attribs);
      if(!gl_context) {
        logger::log("Failed to create OpenGL context.", "Error", logger::color::red);
        return false;
      }

      if(!wglMakeCurrent(hdc, gl_context)) {
        logger::log("Failed to make OpenGL context current.", "Error", logger::color::red);
        return false;
      }
    }

    ShowWindow(window::window, SW_SHOW);

    return true;
  }

  /**
   * Main method to update the window.
   */
  void update_window() {
    MSG msg = {};

    while(PeekMessageA(&msg, window::window, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessageA(&msg);
    }
  }
}  // namespace window