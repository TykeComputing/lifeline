/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_LOGGING_H
#define LE_COMMON_LOGGING_H

#include <LE/common/macros.h>

#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

#include <LE/common/cppformat.h>
#include <LE/common/timer.h>


namespace LE
{

class log_timer
{
public:
  static float get_log_time();

private:
  static steady_timer p_timer;
};

// NOTE: The below logging functions cannot be used until SDL has been initialized.

LE_ENUM_5(log_scope,
  GLOBAL,
  ENGINE,
  GAME,
  GRAPHICS,
  MATH)

void log(FILE * const out_file, char const* format, fmt::ArgList const& args);

void log_status_no_prefix(char const* format, fmt::ArgList const& args);
void log_error_no_prefix(char const* format, fmt::ArgList const& args);

void log_status(char const* format, fmt::ArgList const& args);
void log_error(char const* format, fmt::ArgList const& args);

void log_status(log_scope::value scope, char const* format, fmt::ArgList const& args);
void log_error(log_scope::value scope, char const* format, fmt::ArgList const& args);

FMT_VARIADIC(void, log, FILE * const, const char *)
FMT_VARIADIC(void, log_status_no_prefix, const char *)
FMT_VARIADIC(void, log_error_no_prefix, const char *)
FMT_VARIADIC(void, log_status, const char *)
FMT_VARIADIC(void, log_error, const char *)
FMT_VARIADIC(void, log_status, log_scope::value, const char *)
FMT_VARIADIC(void, log_error, log_scope::value, const char *)

std::string convert_unsigned_string_to_signed(unsigned char const* unsigned_message);

extern char const* const log_line_seperator;
extern char const* const log_line_seperator_sub_1;
extern char const* const log_line_seperator_sub_2;

}

#endif // LE_COMMON_LOGGING_H
