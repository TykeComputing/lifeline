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

#ifndef LE_ENGINE_WINDOW_H
#define LE_ENGINE_WINDOW_H

#include "SDL.h"

namespace LE
{

class window
{
public:
  window();
  ~window();

  void update();

  SDL_Window const* get() const;
  SDL_Window * get();

private:
  SDL_Window * p_raw_window;
};

} // namespace LE

#endif // LE_ENGINE_WINDOW_H
