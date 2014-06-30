/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "window.h"

#include <common/fatal_error.h>
#include <common/fatal_construction_exception.h>

namespace LE
{

window::window()
{
  Uint32 sdl_window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;
  p_raw_window = SDL_CreateWindow("Lifeline Engine", 64, 64, 1280, 760, sdl_window_flags);
  if(p_raw_window == nullptr)
  {
    LE_FATAL_ERROR(SDL_GetError());
    SDL_ClearError();
    throw fatal_construction_exception("Error creating SDL window, exiting...");
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
