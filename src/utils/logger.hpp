#pragma once
#ifndef _LOGGER_HPP
#define _LOGGER_HPP

#include <Windows.h>
#include <stdio.h>

#include <iostream>
#include <string>

namespace logger {
  /**
   * All the possible colors for the console log.
   */
  enum class color
  {
    black,
    blue,
    green,
    cyan,
    red,
    magenta,
    brown,
    light_gray,
    dark_gray,
    light_blue,
    light_green,
    light_cyan,
    light_red,
    light_magenta,
    yellow,
    white
  };

  /**
   * Set the color of the console.
   *
   * @param color The color to set the console to.
   */
  void set_color(color color);

  /**
   * Log a message to the console.
   *
   * @param message The message to log.
   */
  void log(std::string message);

  /**
   * Log a message to the console with a color.
   *
   * @param message The message to log.
   * @param color The color to log the message with.
   */
  void log(std::string message, color color);

  /**
   * Log a message to the console with a prefix.
   *
   * @param message The message to log.
   * @param prefix The prefix to log the message with.
   * @param color The color to log the message with.
   */
  void log(std::string message, std::string prefix, color color = color::white);

  /**
   * Log a message to the console with a prefix and a argument.
   *
   * @param message The message to log.
   * @param arg The argument to log the message with.
   * @param prefix The prefix to log the message with.
   * @param color The color to log the message with.
   */
  template <typename T>
  void log(std::string message, T arg, std::string prefix = "LOG", color color = color::white);
}  // namespace logger

#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak()
#elif __linux__
#define DEBUG_BREAK() __builtin_debugtrap()
#else
#define DEBUG_BREAK() __builtin_trap()
#endif

#define SM_TRACE(...) logger::log(__VA_ARGS__, "TRACE", logger::color::light_gray)
#define SM_INFO(...)  logger::log(__VA_ARGS__, "INFO", logger::color::light_green)
#define SM_WARN(...)  logger::log(__VA_ARGS__, "WARN", logger::color::yellow)
#define SM_ERROR(...) logger::log(__VA_ARGS__, "ERROR", logger::color::red)

#define SM_ASSERT(condition, ...) \
  if(!(condition)) {              \
    SM_ERROR(__VA_ARGS__);        \
    DEBUG_BREAK();                \
  }

#endif  // _LOGGER_HPP