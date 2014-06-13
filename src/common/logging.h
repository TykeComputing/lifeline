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

#include <common/macros.h>

#include <memory>
#include <iostream>
#include <string>

#include <common/cppformat.h>

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

fmt::Formatter<logger> log(std::ostream & os, char const* format);

// NOTE: The below logging functions cannot be used until SDL has been initialized.

LE_ENUM_5(log_scope,
  global,
  engine,
  game,
  graphics,
  math)

fmt::Formatter<logger> log_status(char const* format);
fmt::Formatter<logger> log_error(char const* format);

fmt::Formatter<logger> log_status(log_scope::value scope, char const* format);
fmt::Formatter<logger> log_error(log_scope::value scope, char const* format);

// HELPERS
namespace detail
{

void log_prefix(std::ostream & os, char const* log_type, log_scope::value scope);

} //namespace detail

}

#endif // LE_COMMON_LOGGING_H
