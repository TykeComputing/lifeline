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
#include <iosfwd>
#include <string>

#include <cppformat/format.h>

#include <common/macros.h>

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

fmt::Formatter<logger> log(char const* scope, char const* format);

}

#endif // LE_COMMON_LOGGING_H
