/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "window.h"

#include <LE/common/fatal_error.h>
#include <LE/common/fatal_construction_exception.h>
#include <LE/common/logging.h>

namespace LE
{

window::window()
{
  Uint32 sdl_window_flags = SDL_WINDOW_OPENGL /*| SDL_WINDOW_RESIZABLE*/ | SDL_WINDOW_SHOWN;
  p_raw_window = SDL_CreateWindow("Lifeline Engine", 64, 64, 1280, 768, sdl_window_flags);
  if(p_raw_window == nullptr)
  {
    log_error(log_scope::ENGINE, "Error creating SDL window: {}", SDL_GetError());
    SDL_ClearError();
    throw fatal_construction_exception{};
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

// TODO: Cache size
uvec2 window::get_size() const
{
  int w, h;
  SDL_GetWindowSize(p_raw_window, &w, &h);
  return uvec2(static_cast<unsigned>(w), static_cast<unsigned>(h));
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
