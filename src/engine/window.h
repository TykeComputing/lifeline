/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_WINDOW_H
#define LE_ENGINE_WINDOW_H

#include "SDL.h"

#include <math/vec.h>

namespace LE
{

class window
{
public:
  window();
  ~window();

  void update();

  ivec2 get_size() const;

  SDL_Window const* get_raw() const;
  SDL_Window * get_raw();

private:
  SDL_Window * p_raw_window;
};

} // namespace LE

#endif // LE_ENGINE_WINDOW_H
