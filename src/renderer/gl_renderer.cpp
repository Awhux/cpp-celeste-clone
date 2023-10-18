#include "gl_renderer.hpp"

#include <string.h>

#include "../lib/opengl/glcorearb.h"
#include "../utils/logger.hpp"

namespace gl_renderer {
  void* load_gl_function(char* name) {
    PROC proc = wglGetProcAddress(name);

    if(proc) return (void*)proc;

    // Try to load the function from opengl32.dll
    HMODULE module = LoadLibraryA("opengl32.dll");
    SM_ASSERT(!module, "Failed to load opengl32.dll");

    void* func = (void*)GetProcAddress(module, name);

    FreeLibrary(module);

    if(!func) {
      char error_string[256];
      sprintf(error_string, "Failed to load OpenGL function: %s", name);
      SM_ERROR(error_string);

      return nullptr;
    }

    return func;
  }

  void load_gl_functions() {
    glCreateProgram_ptr           = (PFNGLCREATEPROGRAMPROC)load_gl_function("glCreateProgram");
    glDeleteTextures_ptr          = (PFNGLDELETETEXTURESPROC)load_gl_function("glDeleteTextures");
    glGenTextures_ptr             = (PFNGLGENTEXTURESPROC)load_gl_function("glGenTextures");
    glBindTexture_ptr             = (PFNGLBINDTEXTUREPROC)load_gl_function("glBindTexture");
    glDrawArrays_ptr              = (PFNGLDRAWARRAYSPROC)load_gl_function("glDrawArrays");
    glCreateShader_ptr            = (PFNGLCREATESHADERPROC)load_gl_function("glCreateShader");
    glGetUniformLocation_ptr      = (PFNGLGETUNIFORMLOCATIONPROC)load_gl_function("glGetUniformLocation");
    glUniform1f_ptr               = (PFNGLUNIFORM1FPROC)load_gl_function("glUniform1f");
    glUniform2fv_ptr              = (PFNGLUNIFORM2FVPROC)load_gl_function("glUniform2fv");
    glUniform3fv_ptr              = (PFNGLUNIFORM3FVPROC)load_gl_function("glUniform3fv");
    glUniform1i_ptr               = (PFNGLUNIFORM1IPROC)load_gl_function("glUniform1i");
    glUniformMatrix4fv_ptr        = (PFNGLUNIFORMMATRIX4FVPROC)load_gl_function("glUniformMatrix4fv");
    glVertexAttribDivisor_ptr     = (PFNGLVERTEXATTRIBDIVISORPROC)load_gl_function("glVertexAttribDivisor");
    glActiveTexture_ptr           = (PFNGLACTIVETEXTUREPROC)load_gl_function("glActiveTexture");
    glBufferSubData_ptr           = (PFNGLBUFFERSUBDATAPROC)load_gl_function("glBufferSubData");
    glDrawArraysInstanced_ptr     = (PFNGLDRAWARRAYSINSTANCEDPROC)load_gl_function("glDrawArraysInstanced");
    glBindFramebuffer_ptr         = (PFNGLBINDFRAMEBUFFERPROC)load_gl_function("glBindFramebuffer");
    glCheckFramebufferStatus_ptr  = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)load_gl_function("glCheckFramebufferStatus");
    glGenFramebuffers_ptr         = (PFNGLGENFRAMEBUFFERSPROC)load_gl_function("glGenFramebuffers");
    glFramebufferTexture2D_ptr    = (PFNGLFRAMEBUFFERTEXTURE2DPROC)load_gl_function("glFramebufferTexture2D");
    glDrawBuffers_ptr             = (PFNGLDRAWBUFFERSPROC)load_gl_function("glDrawBuffers");
    glDeleteFramebuffers_ptr      = (PFNGLDELETEFRAMEBUFFERSPROC)load_gl_function("glDeleteFramebuffers");
    glBlendFunci_ptr              = (PFNGLBLENDFUNCIPROC)load_gl_function("glBlendFunci");
    glBlendEquation_ptr           = (PFNGLBLENDEQUATIONPROC)load_gl_function("glBlendEquation");
    glClearBufferfv_ptr           = (PFNGLCLEARBUFFERFVPROC)load_gl_function("glClearBufferfv");
    glShaderSource_ptr            = (PFNGLSHADERSOURCEPROC)load_gl_function("glShaderSource");
    glCompileShader_ptr           = (PFNGLCOMPILESHADERPROC)load_gl_function("glCompileShader");
    glGetShaderiv_ptr             = (PFNGLGETSHADERIVPROC)load_gl_function("glGetShaderiv");
    glGetShaderInfoLog_ptr        = (PFNGLGETSHADERINFOLOGPROC)load_gl_function("glGetShaderInfoLog");
    glAttachShader_ptr            = (PFNGLATTACHSHADERPROC)load_gl_function("glAttachShader");
    glLinkProgram_ptr             = (PFNGLLINKPROGRAMPROC)load_gl_function("glLinkProgram");
    glValidateProgram_ptr         = (PFNGLVALIDATEPROGRAMPROC)load_gl_function("glValidateProgram");
    glGetProgramiv_ptr            = (PFNGLGETPROGRAMIVPROC)load_gl_function("glGetProgramiv");
    glGetProgramInfoLog_ptr       = (PFNGLGETPROGRAMINFOLOGPROC)load_gl_function("glGetProgramInfoLog");
    glGenBuffers_ptr              = (PFNGLGENBUFFERSPROC)load_gl_function("glGenBuffers");
    glGenVertexArrays_ptr         = (PFNGLGENVERTEXARRAYSPROC)load_gl_function("glGenVertexArrays");
    glGetAttribLocation_ptr       = (PFNGLGETATTRIBLOCATIONPROC)load_gl_function("glGetAttribLocation");
    glBindVertexArray_ptr         = (PFNGLBINDVERTEXARRAYPROC)load_gl_function("glBindVertexArray");
    glEnableVertexAttribArray_ptr = (PFNGLENABLEVERTEXATTRIBARRAYPROC)load_gl_function("glEnableVertexAttribArray");
    glVertexAttribPointer_ptr     = (PFNGLVERTEXATTRIBPOINTERPROC)load_gl_function("glVertexAttribPointer");
    glBindBuffer_ptr              = (PFNGLBINDBUFFERPROC)load_gl_function("glBindBuffer");
    glBindBufferBase_ptr          = (PFNGLBINDBUFFERBASEPROC)load_gl_function("glBindBufferBase");
    glBufferData_ptr              = (PFNGLBUFFERDATAPROC)load_gl_function("glBufferData");
    glGetVertexAttribPointerv_ptr = (PFNGLGETVERTEXATTRIBPOINTERVPROC)load_gl_function("glGetVertexAttribPointerv");
    glUseProgram_ptr              = (PFNGLUSEPROGRAMPROC)load_gl_function("glUseProgram");
    glDeleteVertexArrays_ptr      = (PFNGLDELETEVERTEXARRAYSPROC)load_gl_function("glDeleteVertexArrays");
    glDeleteBuffers_ptr           = (PFNGLDELETEBUFFERSPROC)load_gl_function("glDeleteBuffers");
    glDeleteProgram_ptr           = (PFNGLDELETEPROGRAMPROC)load_gl_function("glDeleteProgram");
    glDetachShader_ptr            = (PFNGLDETACHSHADERPROC)load_gl_function("glDetachShader");
    glDeleteShader_ptr            = (PFNGLDELETESHADERPROC)load_gl_function("glDeleteShader");
    glDrawElementsInstanced_ptr   = (PFNGLDRAWELEMENTSINSTANCEDPROC)load_gl_function("glDrawElementsInstanced");
    glGenerateMipmap_ptr          = (PFNGLGENERATEMIPMAPPROC)load_gl_function("glGenerateMipmap");
    glDebugMessageCallback_ptr    = (PFNGLDEBUGMESSAGECALLBACKPROC)load_gl_function("glDebugMessageCallback");
  }

#pragma region OpenGL function wrappers
  GLAPI GLuint APIENTRY glCreateProgram(void) { return glCreateProgram(); }

  GLAPI void APIENTRY glDeleteTextures(GLsizei n, const GLuint* textures) { glDeleteTextures(n, textures); }

  GLAPI void APIENTRY glGenTextures(GLsizei n, GLuint* textures) { glGenTextures(n, textures); }

  GLAPI void APIENTRY glBindTexture(GLenum target, GLuint texture) { glBindTexture(target, texture); }

  void glDrawArrays(GLenum mode, GLint first, GLsizei count) { glDrawArrays(mode, first, count); }

  GLuint glCreateShader(GLenum shaderType) { return glCreateShader(shaderType); }

  GLint glGetUniformLocation(GLuint program, const GLchar* name) { return glGetUniformLocation(program, name); }

  void glUniform1f(GLint location, GLfloat v0) { glUniform1f(location, v0); }

  void glUniform2fv(GLint location, GLsizei count, const GLfloat* value) { glUniform2fv(location, count, value); }

  void glUniform3fv(GLint location, GLsizei count, const GLfloat* value) { glUniform3fv(location, count, value); }

  void glUniform1i(GLint location, GLint v0) { glUniform1i(location, v0); }

  void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    glUniformMatrix4fv(location, count, transpose, value);
  }

  void glVertexAttribDivisor(GLuint index, GLuint divisor) { glVertexAttribDivisor(index, divisor); }

  void glActiveTexture(GLenum texture) { glActiveTexture(texture); }

  void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data) {
    glBufferSubData(target, offset, size, data);
  }

  void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount) {
    glDrawArraysInstanced(mode, first, count, instanceCount);
  }

  void glBindFramebuffer(GLenum target, GLuint framebuffer) { glBindFramebuffer(target, framebuffer); }

  GLenum glCheckFramebufferStatus(GLenum target) { return glCheckFramebufferStatus(target); }

  void glGenFramebuffers(GLsizei n, GLuint* framebuffers) { glGenFramebuffers(n, framebuffers); }

  void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
  }

  void glDrawBuffers(GLsizei n, const GLenum* bufs) { glDrawBuffers(n, bufs); }

  void glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers) { glDeleteFramebuffers(n, framebuffers); }

  void glBlendFunci(GLuint buf, GLenum src, GLenum dst) { glBlendFunci(buf, src, dst); }

  void glBlendEquation(GLenum mode) { glBlendEquation(mode); }

  void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value) {
    glClearBufferfv(buffer, drawbuffer, value);
  }

  void glShaderSource(GLuint shader, GLsizei count, const GLchar* const* strings, const GLint* lengths) {
    glShaderSource(shader, count, strings, lengths);
  }

  void glCompileShader(GLuint shader) { glCompileShader(shader); }

  void glGetShaderiv(GLuint shader, GLenum pname, GLint* params) { glGetShaderiv(shader, pname, params); }

  void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
    glGetShaderInfoLog(shader, bufSize, length, infoLog);
  }

  void glAttachShader(GLuint program, GLuint shader) { glAttachShader(program, shader); }

  void glLinkProgram(GLuint program) { glLinkProgram(program); }

  void glValidateProgram(GLuint program) { glValidateProgram(program); }

  void glGetProgramiv(GLuint program, GLenum pname, GLint* params) { glGetProgramiv(program, pname, params); }

  void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
    glGetProgramInfoLog(program, bufSize, length, infoLog);
  }

  void glGenBuffers(GLsizei n, GLuint* buffers) { glGenBuffers(n, buffers); }

  void glGenVertexArrays(GLsizei n, GLuint* arrays) { glGenVertexArrays(n, arrays); }

  GLint glGetAttribLocation(GLuint program, const GLchar* name) { return glGetAttribLocation(program, name); }

  void glBindVertexArray(GLuint array) { glBindVertexArray(array); }

  void glEnableVertexAttribArray(GLuint index) { glEnableVertexAttribArray(index); }

  void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                             const void* pointer) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  }

  void glBindBuffer(GLenum target, GLuint buffer) { glBindBuffer(target, buffer); }

  void glBindBufferBase(GLenum target, GLuint index, GLuint buffer) { glBindBufferBase(target, index, buffer); }

  void glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) {
    glBufferData(target, size, data, usage);
  }

  void glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer) {
    glGetVertexAttribPointerv(index, pname, pointer);
  }

  void glUseProgram(GLuint program) { glUseProgram(program); }

  void glDeleteVertexArrays(GLsizei n, const GLuint* arrays) { glDeleteVertexArrays(n, arrays); }

  void glDeleteBuffers(GLsizei n, const GLuint* buffers) { glDeleteBuffers(n, buffers); }

  void glDeleteProgram(GLuint program) { glDeleteProgram(program); }

  void glDetachShader(GLuint program, GLuint shader) { glDetachShader(program, shader); }

  void glDeleteShader(GLuint shader) { glDeleteShader(shader); }

  void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount) {
    glDrawElementsInstanced(mode, count, type, indices, instancecount);
  }

  void glGenerateMipmap(GLenum target) { glGenerateMipmap(target); }

  void glDebugMessageCallback(GLDEBUGPROC callback, const void* userParam) {
    glDebugMessageCallback(callback, userParam);
  }
#pragma endregion
}  // namespace gl_renderer