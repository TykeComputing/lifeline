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

#ifndef LE_COMMON_TIMER_H
#define LE_COMMON_TIMER_H

// cstdint Must be incldued before SDL in this case otherwise size_t conflicts (unsure why)
#include <cstdint>
#include <SDL2/SDL_timer.h>

namespace LE
{

// SDL_Init must be called before constructing a timer
class timer
{
public:
  timer(void);

  void reset(void);
  float poll(void) const;

private:
  Uint64 p_perf_count_start = 0u;
  Uint64 p_perf_freq = 0u;
};

} // namespace LE

#endif // LE_COMMON_TIMER_H
