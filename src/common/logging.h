/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_LOGGING_H
#define LE_COMMON_LOGGING_H

#include <common/macros.h>

#include <memory>
#include <iostream>
#include <string>

#include <common/cppformat.h>
#include <common/timer.h>

namespace LE
{

class log_timer
{
public:
  static float get_log_time();

private:
  static steady_timer p_timer;
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
  GLOBAL,
  ENGINE,
  GAME,
  GRAPHICS,
  MATH)

fmt::Formatter<logger> log_status_no_prefix(char const* format);
fmt::Formatter<logger> log_error_no_prefix(char const* format);

fmt::Formatter<logger> log_status(char const* format);
fmt::Formatter<logger> log_error(char const* format);

fmt::Formatter<logger> log_status(log_scope::value scope, char const* format);
fmt::Formatter<logger> log_error(log_scope::value scope, char const* format);

std::string convert_unsigned_string_to_signed(unsigned char const* unsigned_message);

extern char const* log_line_seperator;

// HELPERS
namespace detail
{

void log_prefix(std::ostream & os, char const* log_type, log_scope::value scope);

} //namespace detail

}

#endif // LE_COMMON_LOGGING_H
