/*
************************************************************************************************
Copyright 2014 Peter Clark

This file is part of Lifeline Engine.

Lifeline Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Lifeline Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Lifeline Engine.  If not, see <http://www.gnu.org/licenses/>.
************************************************************************************************
*/

#include "graphics_context.h"

#include <GL/glew.h>

#include <common/fatal_error.h>
#include <common/fatal_construction_exception.h>
#include <common/LE_printf.h>
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

  // Experimental is needed for OpenGL 3.2+ core contexts
  // See: http://www.opengl.org/wiki/OpenGL_Loading_Library
  glewExperimental = GL_TRUE;
  GLenum glew_init_res = glewInit();
  if(glew_init_res != GLEW_OK)
  {
    LE_FATAL_ERROR(glewGetErrorString(glew_init_res));
    throw fatal_construction_exception("Error intializing GLEW, exiting...");
  }

  std::string glew_init_GL_errors = get_GL_errors();
  if(glew_init_GL_errors.empty())
  {
    LE_printf("OpenGL Function Loading: No errors on glewInit...\n");
  }
  else
  {
    LE_printf("OpenGL Function Loading: Errors on glewInit: %s \n",
      glew_init_GL_errors.c_str());
  }

  if(!GLEW_VERSION_3_2)
  {
    throw fatal_construction_exception("Error, unable to obtain OpenGL 3.2 context, exiting...");
  }

  LE_printf("----------------------------------------------------------------\n");
  LE_printf("Graphics Successfully Initialized\n");
  LE_printf("System OpenGL Info\n");
  LE_printf("======================\n");
  LE_printf(" Version: %s\n", glGetString(GL_VERSION));
  LE_printf("  Vendor: %s\n", glGetString(GL_VENDOR));
  LE_printf("Renderer: %s\n", glGetString(GL_RENDERER));
  LE_printf(" Shading: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
  LE_printf("----------------------------------------------------------------\n");
}

graphics_context::~graphics_context()
{
  SDL_GL_DeleteContext(p_raw_context);
}

} // namespace LE
