/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "graphics_context.h"

#include <LE/common/fatal_error.h>
#include <LE/common/fatal_construction_exception.h>
#include <LE/common/logging.h>

#include <LE/graphics/error_checking.h>

#include <LE/engine/window.h>

namespace LE
{

graphics_context::graphics_context(window & target_window)
{
  // Set GL context attributes
  auto LE_SDL_GL_SetAttribute = [](SDL_GLattr attrib, int val)->void
  {
    int set_attrib_res = SDL_GL_SetAttribute(attrib, val);
    if(set_attrib_res != 0)
    {
      LE_FATAL_ERROR("{}", SDL_GetError());
      SDL_ClearError();
    }
  };

  int const LE_GL_version_major = 3;
  int const LE_GL_version_minor = 2;
  LE_SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, LE_GL_version_major);
  LE_SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, LE_GL_version_minor);
#ifdef LE_MODERN_OPENGL_ONLY
  LE_SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#else
  LE_SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
#endif
  LE_SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);

  LE_SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);

  // Create GL context
  p_raw_context = SDL_GL_CreateContext(target_window.get_raw());
  if(p_raw_context == nullptr)
  {
    LE_FATAL_ERROR("{}", SDL_GetError());
    SDL_ClearError();
    throw fatal_construction_exception("Error creating OpenGL context, exiting...");
  }

  // 1 = v-sync, 0 = no v-sync, -1 = dynamic
  SDL_GL_SetSwapInterval(0);

  // Check GL context attributes
  log_status(log_scope::ENGINE, log_line_seperator);

  log_status(log_scope::ENGINE, "OpenGL Context Successfully Created");
  log_status(log_scope::ENGINE, "Attributes");
  log_status(log_scope::ENGINE, log_line_seperator_sub_1);

  int context_attrib_val;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &context_attrib_val);
  log_status(log_scope::ENGINE, "Major Version: {}", context_attrib_val);
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &context_attrib_val);
  log_status(log_scope::ENGINE, "Minor Version: {}", context_attrib_val);
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &context_attrib_val);
  log_status(log_scope::ENGINE, "Context Profile: {}",
    (context_attrib_val == SDL_GL_CONTEXT_PROFILE_CORE) ? "Core" :
    (context_attrib_val == SDL_GL_CONTEXT_PROFILE_COMPATIBILITY) ? "Compatibility" :
    "unknown");

  SDL_GL_GetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, &context_attrib_val);
  log_status(log_scope::ENGINE, "Framebuffer sRGB: {}",
    (context_attrib_val == 1) ? "Enabled" : "Disabled");

  SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &context_attrib_val);
  log_status(log_scope::ENGINE, "Framebuffer Depth: {}", context_attrib_val);

  context_attrib_val = SDL_GL_GetSwapInterval();
  log_status(log_scope::ENGINE, "Swap Interval: {}",
    (context_attrib_val == 0)  ? "Immediate"  :
    (context_attrib_val == 1)  ? "Synchronized" :
    (context_attrib_val == -1) ? "Dynamic" :
    "Unknown");

  log_status(log_scope::ENGINE, log_line_seperator);
}

graphics_context::~graphics_context()
{
  SDL_GL_DeleteContext(p_raw_context);
}

} // namespace LE
