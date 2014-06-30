/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "fatal_error.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

#include <common/logging.h>

namespace LE
{

namespace detail
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
  static bool sdl_init = false;

  if(sdl_init)
  {
    // Since this will only occur during errors, efficiency doesn't matter
    std::string formatted_message =
        file + ":" + function + "(" + std::to_string(line) + ")\n\n" + message;

    log(std::cerr, "HALT - {}") << formatted_message;

    int res = SDL_ShowSimpleMessageBox(
      SDL_MESSAGEBOX_ERROR,
      "LifeLine Engine - FATAL ERROR!",
      formatted_message.c_str(),
      NULL);

    if(res == 0)
    {
      log_error("Assert!\n {}") << SDL_GetError();
      SDL_ClearError();
    }
  }
  else
  {
    sdl_init = (SDL_WasInit(0) != 0);
    log(std::cerr, "Attempting to display assert message box before SDL_Init!");
  }

  std::cout.flush();
  std::cerr.flush();
}

}

}
