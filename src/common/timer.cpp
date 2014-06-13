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


high_resolution_timer::high_resolution_timer(void)
{

}

void high_resolution_timer::start(void)
{
  reset();
}

void high_resolution_timer::reset(void)
{
  p_perf_freq = SDL_GetPerformanceFrequency();
  p_perf_count_start = SDL_GetPerformanceCounter();

  p_is_running = true;
}

float high_resolution_timer::poll(void) const
{
  if(p_is_running == false)
  {
    LE_ERROR("Attemtping to poll high resolution timer that was not started.");
    return 0.0f;
  }

  LE_ERRORIF(p_perf_freq != SDL_GetPerformanceFrequency(),
    "high_resolution_timer error, frequency when polled is different from frequency when reset!");

  // In the event of wrap around we will assume only one wrap has occured, and end < start.
  //   All other cases will be ignored.
  Uint64 perf_count_end = SDL_GetPerformanceCounter();

  Uint64 perf_count_elapsed;
  if(perf_count_end > p_perf_count_start)
  {
    perf_count_elapsed = perf_count_end - p_perf_count_start;
  }
  else
  {
    perf_count_elapsed =
      (std::numeric_limits<Uint64>::max() - p_perf_count_start) + perf_count_end;
  }

  return static_cast<float>(perf_count_elapsed) / p_perf_freq;
}

} // namespace LE
