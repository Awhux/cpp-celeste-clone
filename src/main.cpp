#include <stdio.h>

#include <iostream>
#include <string>

#define _CRT_SECURE_NO_WARNINGS 1

// Local files
#include "game.hpp"
#include "window.hpp"

// Folders in src/
#include "renderer/gl_renderer.hpp"
#include "utils/logger.hpp"

int main() {
  SM_TRACE("Starting Celeste...");
  SM_ASSERT(window::create_window(400, 400, "Celeste Window"), "Failed to create window!");

  SM_TRACE("Starting game loop...");
  while(game::running) { window::update_window(); }

  SM_TRACE("Stopping Celeste...");
  return 0;
}