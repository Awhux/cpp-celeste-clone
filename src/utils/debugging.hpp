#pragma once
#ifndef _DEBUGGING_HPP
#define _DEBUGGING_HPP

#include <stdio.h>

#include <stdexcept>

namespace debugging {
  /**
   * Is in debug mode.
   */
  inline bool debug_mode = false;

  /**
   * Set the debug mode.
   *
   * @param mode The mode to set the debug mode to.
   */
  void set_debug_mode(bool mode) { debug_mode = mode; }

  /**
   * Save debug information to a file.
   */
  void save_debug_info() {
    if(!debug_mode) return;

    throw std::runtime_error("Not implemented.");
  }
}  // namespace debugging

#endif  // _DEBUGGING_HPP