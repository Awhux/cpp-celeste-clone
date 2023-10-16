#pragma once
#ifndef _WINDOW_HPP
#define _WINDOW_HPP

// Windows platform
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#endif

#include <string>

namespace window {
  static HWND window;

  /**
   * Main method to create a window.
   *
   * @param width The width of the window.
   * @param height The height of the window.
   * @param title The title of the window.
   */
  bool create_window(int width, int height, std::string title);

  /**
   * Main method to update the window.
   */
  void update_window();

  /**
   * Window callback
   */
  LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}  // namespace window

#endif