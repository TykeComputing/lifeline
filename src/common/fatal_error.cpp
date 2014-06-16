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
      "LifeLine Engine - ERROR!",
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
