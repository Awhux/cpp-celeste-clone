#pragma once
#ifndef _GL_RENDERER_HPP
#define _GL_RENDERER_HPP

#define APIENTRY

#include "../lib/opengl/glcorearb.h"
#include "../utils/logger.hpp"
#include "../utils/utils.hpp"

namespace gl_renderer {
  static PFNGLCREATEPROGRAMPROC glCreateProgram;

  void load_gl_functions() {
    glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");

    SM_ASSERT(!glCreateProgram, "Failed to load glCreateProgram!");

    SM_TRACE("Loaded OpenGL functions!");
  }
}  // namespace gl_renderer

#endif  // _GL_RENDERER_HPP