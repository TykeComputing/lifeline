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

#include <cstdio>

#include <GL/glew.h>
#include <GL/gl.h>
#include "SDL.h"

#define LE_ERROR(msg) std::printf("%s:%s(%d) | %s\n", __FILE__, __FUNCTION__, __LINE__, msg)
#define LE_PRINT_SDL_ERROR() LE_ERROR(SDL_GetError()); SDL_ClearError()
#define LE_UNUSED_VAR(x) (void)

void LE_SDL_GL_SetAttribute(SDL_GLattr attrib, int val)
{
  int set_attrib_res = SDL_GL_SetAttribute(attrib, val);
  if(set_attrib_res != 0)
  {
    LE_PRINT_SDL_ERROR();
  }
}

int main(int arg_count, char *args[])
{
  LE_UNUSED_VAR(arg_count);
  LE_UNUSED_VAR(args);

  //// Initialize

  /// SDL
  int sdl_init_res = SDL_Init(SDL_INIT_VIDEO);
  if(sdl_init_res = 0)
  {
    LE_ERROR("OS Init: Error initializing SDL, exiting...\n");
    LE_PRINT_SDL_ERROR();
    return -1;
  }

  int const LE_GL_version_major = 3;
  int const LE_GL_version_minor = 2;
  LE_SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, LE_GL_version_major);
  LE_SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, LE_GL_version_minor);
  LE_SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);

  Uint32 sdl_window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;
  SDL_Window * app_window = SDL_CreateWindow("Lifeline Engine", 64, 64, 1280, 760, sdl_window_flags);
  if(app_window == nullptr)
  {
    LE_ERROR("OS Init: Error creating SDL window, exiting...\n");
    LE_PRINT_SDL_ERROR();
    return -1;
  }

  SDL_GLContext graphics_context = SDL_GL_CreateContext(app_window);
  if(graphics_context == nullptr)
  {
    LE_ERROR("OS Init: Error creating OpenGL context, exiting...\n");
    LE_PRINT_SDL_ERROR();
    return -1;
  }

  /// GLEW

  // TODO - Verify if I actually need glewExperimental
  glewExperimental = true;
  GLenum glew_init_res = glewInit();
  if(glew_init_res != GLEW_OK)
  {
    LE_ERROR("Graphics Init: Error intializing GLEW, exiting...\n");
    LE_ERROR(glewGetErrorString(glew_init_res));
    // Will worry about proper clean up when this functionality is moved to classes
    return -1;
  }

  if(!GLEW_VERSION_3_2)
  {
    // TODO - Make custom string class and use that everywhere instead of raw c-strings.
    //        (With goal being easily manipulated but fast).
    LE_ERROR("Error! Unable to retreive OpenGL 3.2 context, exiting...\n");
    return -1;
  }

  //// Update
  glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

  bool is_running = true;
  while(is_running)
  {
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_Event curr_event;
    while(SDL_PollEvent(&curr_event))
    {
      switch(curr_event.type)
      {
        case SDL_QUIT:
        {
          is_running = false;
        }
        break;
      }
    }

    SDL_GL_SwapWindow(app_window);
  }


  //// Teardown
  SDL_Quit();

  return 0;
}
