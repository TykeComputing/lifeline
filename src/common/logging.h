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

#ifndef LE_COMMON_LOGGING_H
#define LE_COMMON_LOGGING_H

#include <memory>
#include <iostream>
#include <string>

#define FMT_USE_NOEXCEPT 1
#define FMT_USE_VARIADIC_TEMPLATES 1
#define FMT_USE_RVALUE_REFERENCES 1
#include <cppformat/format.h>

namespace LE
{

// fwd-decl
class high_resolution_timer;

class log_timer
{
public:
  static void start();
  static float get_log_time();

private:
  static std::unique_ptr<high_resolution_timer> p_timer;
};

class logger
{
public:
  logger(std::ostream & os, bool print_newline = true);
  logger(logger const& rhs);
  logger const& operator=(logger const& rhs) = delete;

  void operator()(fmt::Writer const& w) const;

private:
  std::ostream & p_os;
  bool p_print_newline;
};

void log(std::ostream & os, char const* format)
{
  fmt::Formatter<logger> f{format, logger{os}};
  return f;
}

// NOTE: The below logging functions cannot be used until SDL has been initialized.
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

// Ideally these would be defined elsewhere (since common would have no knowledge of other
//   libraries). Placing here for the time being for convenience.


// HELPERS
namespace detail
{

void log_prefix(std::ostream & os, char const* log_type, char const* log_scope);

} //namespace detail

}

#endif // LE_COMMON_LOGGING_H
