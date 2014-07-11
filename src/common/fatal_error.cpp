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

#include <common/cppformat.h>
#include <common/logging.h>

namespace LE
{

namespace internal
{

void display_assert(
  std::string const& file,
  std::string const& function,
  int line,
  char const* message)
{
  display_assert(file, function, line, std::string(message));
}

void display_assert(
  std::string const& file,
  std::string const& function,
  int line,
  std::string const& message)
{
  if(SDL_WasInit(0) == 0)
  {
    log(stderr, "Attempting to display assert message box before SDL_Init!");
    return;
  }

  // Since this will only occur during errors, efficiency doesn't matter
  std::string formatted_message =
    fmt::format("{}:{}({})\n\n{}", file, function, line, message);

  log(stderr, "HALT - {}", formatted_message);

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
