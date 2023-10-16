#include "logger.hpp"

namespace logger {
  /**
   * Set the color of the console.
   *
   * @param color The color to set the console to.
   */
  void set_color(color color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<int>(color));
  }

  /**
   * Log a message to the console.
   *
   * @param message The message to log.
   */
  void log(std::string message) { std::cout << message << std::endl; }

  /**
   * Log a message to the console with a color.
   *
   * @param message The message to log.
   * @param color The color to log the message with.
   */
  void log(std::string message, color color) {
    set_color(color);
    printf("%s\n", message.c_str());
    set_color(color::white);
  }

  /**
   * Log a message to the console with a prefix.
   *
   * @param message The message to log.
   * @param prefix The prefix to log the message with.
   * @param color The color to log the message with.
   */
  void log(std::string message, std::string prefix, color color) {
    set_color(color);
    printf("[%s] %s\n", prefix.c_str(), message.c_str());
    set_color(color::white);
  }

  /**
   * Log a message to the console with a prefix and a argument.
   *
   * @param message The message to log.
   * @param arg The argument to log the message with.
   * @param prefix The prefix to log the message with.
   * @param color The color to log the message with.
   */
  template <typename T>
  void log(std::string message, T arg, std::string prefix, color color) {
    set_color(color);
    // If the message has a {} in it, replace it with the argument.
    // TODO: Make this work with multiple arguments.
    // TODO: Add more transformations, like {} -> std::to_string(arg), etc.
    if(message.find("{}") != std::string::npos) { message.replace(message.find("{}"), 2, std::to_string(arg)); }

    printf("[%s] %s\n", prefix.c_str(), message.c_str());

    set_color(color::white);
  }
}  // namespace logger