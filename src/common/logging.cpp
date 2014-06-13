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

#include <common/timer.h>

namespace LE
{

std::unique_ptr<high_resolution_timer> log_timer::p_timer = {};

void log_timer::start()
{
  p_timer.reset(new high_resolution_timer);
}

float log_timer::get_log_time()
{
  if(p_timer == nullptr)
  {
    // Indicate that this was called in the land before timer.
    return -1.0f;
  }
  else
  {
    return p_timer->poll();
  }
}

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

void log(std::ostream & os, char const* format)
{
  fmt::Formatter<logger> f{format, logger{os}};
  return f;
}

void log_status(char const* format)
{
  auto & os = std::cout;
  fmt::Formatter<logger> f{format, logger{os}};
  detail::log_prefix(os, "STATUS", "GLOBAL");
  return f;
}

void log_error(char const* format)
{
  auto & os = std::cerr;
  detail::log_prefix(os, "STATUS", "GLOBAL");
  fmt::Formatter<logger> f{format, logger{os}};
  return f;
}

// HELPERS
namespace detail
{

void log_prefix(std::ostream & os, char const* log_type, char const* log_scope)
{
  try
  {
    fmt::Formatter<logger> log_prefix_f{"({:6.2f}) {} - {}: ", logger{os, false}};
    log_prefix_f << log_timer::get_log_time() << log_type << log_scope;
  }
  catch(fmt::FormatError const& e)
  {
    std::cerr << e.what();
  }
}

} // namespace detail

}
