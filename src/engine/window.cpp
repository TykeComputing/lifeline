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

#include "window.h"

#include <common/error.h>
#include <common/fatal_construction_exception.h>

namespace LE
{

window::window()
{
  Uint32 sdl_window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;
  p_raw_window = SDL_CreateWindow("Lifeline Engine", 0, 0, 1280, 760, sdl_window_flags);
  if(p_raw_window == nullptr)
  {
    LE_ERROR(SDL_GetError());
    SDL_ClearError();
    throw fatal_construction_exception("Error creating SDL window, exiting...\n");
  }
}

window::~window()
{
  SDL_DestroyWindow(p_raw_window);
}

void window::update()
{
  SDL_GL_SwapWindow(p_raw_window);
}

SDL_Window const* window::get_raw() const
{
  return p_raw_window;
}

SDL_Window * window::get_raw()
{
  return p_raw_window;
}

} // namespace LE
