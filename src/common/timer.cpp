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

#include "timer.h"

#include <common/error.h>

#include <SDL2/SDL.h>

namespace LE
{


timer::timer(void)
{
  reset();
}

void timer::reset(void)
{
  p_perf_freq = SDL_GetPerformanceFrequency();
  p_perf_count_start = SDL_GetPerformanceCounter();
}

float timer::poll(void) const
{
  Uint64 perf_count_end = SDL_GetPerformanceCounter();
  Uint64 perf_count_elapsed = perf_count_end - p_perf_count_start;

  LE_ERRORIF(p_perf_freq != SDL_GetPerformanceFrequency(),
    "Timer error, frequency when polled is different from frequency when reset!");
  return static_cast<float>(perf_count_elapsed) / p_perf_freq;
}

} // namespace LE
