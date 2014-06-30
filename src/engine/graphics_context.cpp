/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "graphics_context.h"

#include <GL/glew.h>

#include <common/fatal_error.h>
#include <common/fatal_construction_exception.h>
#include <common/logging.h>

#include <graphics/error_checking.h>

#include <engine/window.h>

namespace LE
{

graphics_context::graphics_context(window & target_window)
{
  p_raw_context = SDL_GL_CreateContext(target_window.get_raw());
  if(p_raw_context == nullptr)
  {
    LE_FATAL_ERROR(SDL_GetError());
    SDL_ClearError();
    throw fatal_construction_exception("Error creating OpenGL context, exiting...");
  }

  // 1  = v-sync
  // 0  = no v-sync
  // -1 = dynamic
  SDL_GL_SetSwapInterval(0);

  // Experimental is needed for OpenGL 3.2+ core contexts
  // See: http://www.opengl.org/wiki/OpenGL_Loading_Library
  glewExperimental = GL_TRUE;
  GLenum glew_init_res = glewInit();
  if(glew_init_res != GLEW_OK)
  {
    LE_FATAL_ERROR(
      convert_unsigned_string_to_signed( glewGetErrorString(glew_init_res) ).c_str());
    throw fatal_construction_exception("Error intializing GLEW, exiting...");
  }

  std::string glew_init_GL_errors = get_GL_errors();
  if(glew_init_GL_errors.empty())
  {
    log_status(log_scope::ENGINE, "OpenGL Function Loading: No errors on glewInit...");
  }
  else
  {
    log_status(log_scope::ENGINE, "OpenGL Function Loading: Errors on glewInit: {} ...")
      << glew_init_GL_errors.c_str();
  }

  if(!GLEW_VERSION_3_2)
  {
    throw fatal_construction_exception("Error, unable to obtain OpenGL 3.2 context, exiting...");
  }

  log_status(log_scope::ENGINE, log_line_seperator);
  log_status(log_scope::ENGINE, "Graphics Successfully Initialized");
  log_status(log_scope::ENGINE, "System OpenGL Info");
  log_status(log_scope::ENGINE, "======================");
  log_status(log_scope::ENGINE, " Version: {}")
    << convert_unsigned_string_to_signed( glGetString(GL_VERSION) ).c_str();
  log_status(log_scope::ENGINE, "  Vendor: {}")
    << convert_unsigned_string_to_signed( glGetString(GL_VENDOR) ).c_str();
  log_status(log_scope::ENGINE, "Renderer: {}")
    << convert_unsigned_string_to_signed( glGetString(GL_RENDERER) ).c_str();
  log_status(log_scope::ENGINE, " Shading: {}")
    << convert_unsigned_string_to_signed( glGetString(GL_SHADING_LANGUAGE_VERSION) ).c_str();
  log_status(log_scope::ENGINE, log_line_seperator);
}

graphics_context::~graphics_context()
{
  SDL_GL_DeleteContext(p_raw_context);
}

} // namespace LE
