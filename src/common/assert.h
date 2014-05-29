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

#ifndef LE_COMMON_ASSERT_H
#define LE_COMMON_ASSERT_H

#include <ostream>
#include <string>

#include <SDL2/SDL.h>

#define LE_ERRORIF(cond, msg) { if(cond) { display_error_message(__FILE__, __FUNCTION__, __LINE__, msg); assert(!cond); } }
#define LE_ERROR(msg) display_error_message(__FILE__, __FUNCTION__, __LINE__, msg); assert(true)

namespace LE
{
  void display_error_message(
    char const* file,
    char const* function,
    int line,
    char const* message)
  {
    std::string formatted_message =
        file + ":" + function + "(" + std::tostring(line) + ") | " + message;

    int res = SDL_ShowSimpleMessageBox(
      SDL_MESSAGEBOX_ERROR,
      "LifeLine Engine - ERROR!",
      formatted_message.c_str(),
      NULL);

    if(res != 0)
    {
      std::cerr << "Attempting to display error message before SDL_Init()!" << std::endl;
      std::cerr << formatted_message << std::endl;
    }
  }
}

#endif // LE_COMMON_ASSERT_H
