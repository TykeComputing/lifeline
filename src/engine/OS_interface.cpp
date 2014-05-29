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

#include "OS_interface.h"

#include <common/error.h>
#include <common/fatal_construction_exception.h>

namespace LE
{

OS_interface::OS_interface()
{
  int sdl_init_res = SDL_Init(SDL_INIT_VIDEO);
  if(sdl_init_res != 0)
  {
    LE_ERROR(SDL_GetError());
    SDL_ClearError();
    throw fatal_construction_exception("Error initializing SDL, exiting...\n");
  }

  auto LE_SDL_GL_SetAttribute = [](SDL_GLattr attrib, int val)->void
  {
    int set_attrib_res = SDL_GL_SetAttribute(attrib, val);
    if(set_attrib_res != 0)
    {
      LE_ERROR(SDL_GetError());
      SDL_ClearError();
    }
  };

  int const LE_GL_version_major = 3;
  int const LE_GL_version_minor = 2;
  LE_SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, LE_GL_version_major);
  LE_SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, LE_GL_version_minor);
  LE_SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
}

OS_interface::~OS_interface()
{
  SDL_Quit();
}

// TODO - Remove return value, have quit signaled via message once messaging system in place.
bool OS_interface::update()
{
  SDL_Event curr_event;
  while(SDL_PollEvent(&curr_event))
  {
    switch(curr_event.type)
    {
      case SDL_QUIT:
      {
        return false;
      }
      break;
    }
  }

  return true;
}

} // namespace LE
