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

#include <chrono>
#include <limits>

// cstdint Must be incldued before SDL in this case otherwise size_t conflicts (unsure why)
#include <cstdint>
#include <SDL2/SDL_timer.h>

namespace LE
{

/*
 * A timer that (generally) uses the highest precision methods available for a given platform.
 *   This should be used instead of std::chrono::high_resolution::clock since MSVC does not
 *   actually implement it.
 *
 * Must be explicitly started. See below warning for explanation.
 *
 * WARNING: Should not be left without resetting for an extended period of timer. Ideal scenario
 *  would involve resetting timer every couple seconds at bare minimum. Otherwise time will
 *  continuously wrap around and reported time will be within the range of a few seconds
 *  depending on the range of the underlying timer.
 *
 *  See: https://connect.microsoft.com/VisualStudio/feedback/details/719443/c-chrono-headers-high-resolution-clock-does-not-have-high-resolution
 */
class high_resolution_timer
{
public:
  void start();

  void reset();
  float poll() const;

private:
  Uint64 p_perf_count_start = 0u;
  Uint64 p_perf_freq = 0u;
  bool p_is_running = false;
};

/*
 * A timer that uses potentially low precision but can measure much greater spans of time than
 *   a high_resolution_timer.
 *
 * Implicitly started when created.
 */
class steady_timer
{
public:
  void reset();
  float poll() const;

private:
  typedef std::chrono::steady_clock::time_point time_point;

  time_point p_time_start = std::chrono::steady_clock::now();
};

} // namespace LE

#endif // LE_COMMON_TIMER_H
