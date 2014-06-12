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

#include "logging.h"

#include <iostream>

#include <SDL2/SDL.h>

#include <common/timer.h>

namespace LE
{

namespace detail
{

std::unique_ptr<timer> log_time::p_timer = {};

void log_time::start_log_timer()
{
  p_timer.reset(new timer);
}

float log_time::get_log_time()
{
  return p_timer->poll();
}

void log_prefix(std::ostream & os, char const* log_type, char const* log_scope)
{
  static bool sdl_init = false;

  if(sdl_init)
  {
    fmt::Formatter<logger> log_prefix_f{"({}) {} - {}: ", logger{os, false}};
    log_prefix_f << log_time::get_log_time() << log_type << log_scope;
  }
  else
  {
    sdl_init = SDL_WasInit(0) != 0;
    fmt::Formatter<logger> log_prefix_f{"{} - {}: ", logger{os, false}};
    log_prefix_f << log_type << log_scope;
  }
}

} // namespace detail

logger::logger(std::ostream & os, bool print_newline) :
  p_os(os),
  p_print_newline(print_newline)
{

}

logger::logger(logger const& rhs) :
  p_os(rhs.p_os),
  p_print_newline(rhs.p_print_newline)
{

}

void logger::operator()(fmt::Writer const& w) const
{
  p_os << w.str();
  if(p_print_newline)
  {
    p_os << std::endl;
  }
}

fmt::Formatter<logger> log(char const* scope, char const* format)
{
  std::ostream & os = std::cout;
  detail::log_prefix(os, "status", scope);

  fmt::Formatter<logger> f{format, logger{os}};
  return f;
}

}
