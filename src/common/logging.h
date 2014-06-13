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

class high_resolution_timer;

namespace detail
{

void log_prefix(std::ostream & os, char const* log_type, char const* log_scope);

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
#define test1
#ifdef test
  template<typename FIRST_T, typename... ARG_TYPES>
  static void
  aux_log(
    fmt::Formatter<logger> & f,
    FIRST_T const& first,
    ARG_TYPES const&... arg_vals)
  {
    f << first;
    aux_log<ARG_TYPES...>(f, arg_vals...);
  }

  template<typename... ARG_TYPES>
  static void aux_log(fmt::Formatter<logger> &)
  {
    // Do nothing
  }
};
#else
  void gun(fmt::Formatter<logger> const&) {}

  template<typename... ARG_TYPES>
  static void
  aux_log(
    fmt::Formatter<logger> & f,
    ARG_TYPES const&... arg_vals)
  {

    gun(f.operator<<(arg_vals)...);
  }
};
#endif
} //namespace detail

class log_timer
{
public:
  static void start();
  static float get_log_time();

private:
  static std::unique_ptr<high_resolution_timer> p_timer;
};

// os - error should be cerr
// safe_log to log with no dependencies.

// Has no dependencies, can be used anywhere.
template<typename... ARG_TYPES>
void
safe_log(
  std::ostream & os,
  char const* format,
  ARG_TYPES const&... args_vals)
{
  try
  {
    fmt::Formatter<detail::logger> f{format, detail::logger{os}};
    detail::log_impl::aux_log<ARG_TYPES...>(f, args_vals...);
  }
  catch(fmt::FormatError const& e)
  {
    std::cerr << e.what();
  }
}

template<typename... ARG_TYPES>
void
log(
  std::ostream & os,
  char const* log_type,
  char const* log_scope,
  char const* format,
  ARG_TYPES const&... args_vals)
{
  detail::log_prefix(os, log_type, log_scope);
  safe_log<ARG_TYPES...>(os, format, args_vals...);
}

template<typename... ARG_TYPES>
void
log_status(
  char const* log_scope,
  char const* format,
  ARG_TYPES const&... arg_vals)
{
  log(std::cout, "status", log_scope, format, arg_vals...);
}

template<typename... ARG_TYPES>
void log_error(
  char const* log_scope,
  char const* format,
  ARG_TYPES const&... arg_vals)
{
  log(std::cerr, "error", log_scope, format, arg_vals...);
}

template<typename... ARG_TYPES>
void
log_global_status(
  char const* format,
  ARG_TYPES const&... arg_vals)
{
  log_status("global", format, arg_vals...);
}

template<typename... ARG_TYPES>
void
log_global_error(
  char const* format,
  ARG_TYPES const&... arg_vals)
{
  log_error("global", format, arg_vals...);
}

}

#endif // LE_COMMON_LOGGING_H
