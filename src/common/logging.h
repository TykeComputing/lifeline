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

class timer;

namespace detail
{

class log_time
{
public:
  static void start_log_timer();
  static float get_log_time();

private:
  static std::unique_ptr<timer> p_timer;
};

void log_prefix(std::ostream & os, char const* log_type, char const* log_scope);

} //namespace detail

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

class log_impl
{
public:
  template<typename FIRST_T, typename... Ts>
  static void aux_log(fmt::Formatter<logger> & f, FIRST_T const& first, Ts const&... vs)
  {
    f << first;
    aux_log<Ts...>(f, vs...); // why does this call this overload instead of the below?
  }

  template<typename... Ts>
  static void aux_log(fmt::Formatter<logger> &)
  {
    // End of recursion
  }
};

template<typename... Ts>
void log(char const* log_type, char const* log_scope, char const* format, Ts const&... vs)
{
  std::ostream & os = std::cout;
  detail::log_prefix(os, log_type, log_scope);

  fmt::Formatter<logger> f{format, logger{os}};
  log_impl::aux_log<Ts...>(f, vs...);
}

template<typename... Ts>
void log_status(char const* format, Ts const&... vs)
{
  log("status", "global", format, vs...);
}

template<typename... Ts>
void log_error(char const* format, Ts const&... vs)
{
  log("error", "global", format, vs...);
}

}

#endif // LE_COMMON_LOGGING_H
