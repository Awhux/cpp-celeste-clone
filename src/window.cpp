#include "window.hpp"

#include <stdio.h>

#include <iostream>

#include "game.hpp"

namespace window {
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
   * Main method to create a window.
   *
   * @param width The width of the window.
   * @param height The height of the window.
   * @param title The title of the window.
   */
  bool create_window(int width, int height, std::string title) {
    HINSTANCE hInstance = GetModuleHandleA(0);  // Get the current instance

    // The window class
    WNDCLASSA wc     = {};
    wc.hInstance     = hInstance;
    wc.lpszClassName = "Window";
    wc.hIcon         = LoadIcon(hInstance, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(0, IDC_ARROW);
    wc.lpfnWndProc   = window::window_callback;

    if(!RegisterClassA(&wc)) {
      MessageBoxA(0, "Failed to register window class.", "Error", MB_ICONERROR);
      return false;
    }

    // Create the window
    window::window = CreateWindowExA(0, "Window", title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                                     width, height, 0, 0, hInstance, 0);

    if(!window::window) {
      MessageBoxA(0, "Failed to create window.", "Error", MB_ICONERROR);
      return false;
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