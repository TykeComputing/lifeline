/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "timer.h"

#include <common/fatal_error.h>

#include <SDL2/SDL.h>

namespace LE
{


void high_resolution_timer::start()
{
  reset();
}

void high_resolution_timer::reset()
{
  p_perf_freq = SDL_GetPerformanceFrequency();
  p_perf_count_start = SDL_GetPerformanceCounter();

  p_is_running = true;
}

float high_resolution_timer::poll() const
{
  if(p_is_running == false)
  {
    LE_FATAL_ERROR("Attemtping to poll high resolution timer that was not started.");
    return 0.0f;
  }

  LE_FATAL_ERROR_IF(p_perf_freq != SDL_GetPerformanceFrequency(),
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

void steady_timer::reset()
{
  p_time_start = std::chrono::steady_clock::now();
}

float steady_timer::poll() const
{
  time_point time_end = std::chrono::steady_clock::now();
  std::chrono::duration<float> duration = time_end - p_time_start;
  return duration.count();
}

} // namespace LE
