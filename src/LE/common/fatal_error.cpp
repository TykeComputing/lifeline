/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "fatal_error.h"

#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>

#include <LE/common/cppformat.h>
#include <LE/common/logging.h>

namespace LE
{

namespace internal
{

void display_assert(
  char const* file,
  char const* function,
  int line,
  char const* format,
  fmt::ArgList const& args)
{
  if(SDL_WasInit(0) == 0)
  {
    log(stderr, "Attempting to display assert message box before SDL_Init!");
    return;
  }

  // Since this will only occur during errors, efficiency doesn't matter
  std::string format_with_file_info =
    fmt::format("HALT {}:{}({})\n  {}", file, function, line, format);

  std::string formatted_message =
    fmt::format(format_with_file_info.c_str(), args);

  ::LE::log_error(formatted_message.c_str());

  int res = SDL_ShowSimpleMessageBox(
    SDL_MESSAGEBOX_ERROR,
    "LifeLine Engine - FATAL ERROR!",
    formatted_message.c_str(),
    NULL);

  if(res == 0)
  {
    log_error("Assert!\n {}", SDL_GetError());
    SDL_ClearError();
  }

  std::cout.flush();
  std::cerr.flush();
}

}

}
