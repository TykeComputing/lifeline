/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "logging.h"

#include <vector>

namespace LE
{

// HELPERS
namespace detail
{

void log_prefix(FILE * const out_file, char const* log_type, log_scope::value scope)
{
  fmt::print(out_file, "({:>6.2f}){:<6}|{:<8}|",
    log_timer::get_log_time(), log_type, log_scope::c_str[scope]);
}

} // namespace detail


steady_timer log_timer::p_timer = {};

float log_timer::get_log_time()
{
  return p_timer.poll();
}

static FILE * const status_file = stdout;
static FILE * const error_file = stderr;

void log(FILE * const out_file, char const* format, fmt::ArgList const& args)
{
  fmt::print(out_file, format, args);
  fmt::print(out_file, "\n");
  fflush(out_file);
}

void log_status_no_prefix(char const* format, fmt::ArgList const& args)
{
  auto * const out_file = status_file;
  log(out_file, format, args);
}

void log_error_no_prefix(char const* format, fmt::ArgList const& args)
{
  auto * const out_file = error_file;
  log(out_file, format, args);
}

void log_status(char const* format, fmt::ArgList const& args)
{
  auto * const out_file = status_file;
  detail::log_prefix(out_file, "STATUS", log_scope::GLOBAL);
  log(out_file, format, args);
}

void log_error(char const* format, fmt::ArgList const& args)
{
  auto * const out_file = error_file;
  detail::log_prefix(out_file, "ERROR", log_scope::GLOBAL);
  log(out_file, format, args);
}

void log_status(log_scope::value scope, char const* format, fmt::ArgList const& args)
{
  auto * const out_file = status_file;
  detail::log_prefix(out_file, "STATUS", scope);
  log(out_file, format, args);
}

void log_error(log_scope::value scope, char const* format, fmt::ArgList const& args)
{
  auto * const out_file = error_file;
  detail::log_prefix(out_file, "ERROR", scope);
  log(out_file, format, args);
}

std::string convert_unsigned_string_to_signed(unsigned char const* unsigned_message)
{
  unsigned char const* unsigned_strlen_it = unsigned_message;
  while(*unsigned_strlen_it != 0)
  {
    ++unsigned_strlen_it;
  }
  size_t message_len = unsigned_strlen_it - unsigned_message;

  std::vector<char> signed_message;
  signed_message.resize(message_len);
  std::transform(
    unsigned_message, unsigned_message + message_len,
    signed_message.begin(),
   [](unsigned char c)->char { return static_cast<char>(c); });

   return {signed_message.begin(), signed_message.end()};
}

char const* const log_line_seperator =
  "----------------------------------------------------------------";

char const* const log_line_seperator_sub_1 =
  "--------------------------------";

char const* const log_line_seperator_sub_2 =
  "----------------";
}
