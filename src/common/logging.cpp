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
  p_timer->start();
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

static std::ostream & status_os = std::cout;
static std::ostream & error_os = std::cerr;

fmt::Formatter<logger> log(std::ostream & os, char const* format)
{
  fmt::Formatter<logger> f{format, logger{os}};
  return f;
}

fmt::Formatter<logger> log_status_no_prefix(char const* format)
{
  auto & os = status_os;
  fmt::Formatter<logger> f{format, logger{os}};
  return f;
}

fmt::Formatter<logger> log_error_no_prefix(char const* format)
{
  auto & os = error_os;
  fmt::Formatter<logger> f{format, logger{os}};
  return f;
}

fmt::Formatter<logger> log_status(char const* format)
{
  auto & os = status_os;
  detail::log_prefix(os, "STATUS", log_scope::global);
  fmt::Formatter<logger> f{format, logger{os}};
  return f;
}

fmt::Formatter<logger> log_error(char const* format)
{
  auto & os = error_os;
  detail::log_prefix(os, "ERROR", log_scope::global);
  fmt::Formatter<logger> f{format, logger{os}};
  return f;
}

fmt::Formatter<logger> log_status(log_scope::value scope, char const* format)
{
  auto & os = status_os;
  detail::log_prefix(os, "STATUS", scope);
  fmt::Formatter<logger> f{format, logger{os}};
  return f;
}

fmt::Formatter<logger> log_error(log_scope::value scope, char const* format)
{
  auto & os = error_os;
  detail::log_prefix(os, "ERROR", scope);
  fmt::Formatter<logger> f{format, logger{os}};
  return f;
}

char const* log_line_seperator =
  "----------------------------------------------------------------";

// HELPERS
namespace detail
{

void log_prefix(std::ostream & os, char const* log_type, log_scope::value scope)
{
  try
  {
    fmt::Formatter<logger> log_prefix_f{"({:<6.2f}) {} - {}: ", logger{os, false}};
    log_prefix_f << log_timer::get_log_time() << log_type << log_scope::c_str[scope];
  }
  catch(fmt::FormatError const& e)
  {
    std::cerr << e.what();
  }
}

} // namespace detail

}
