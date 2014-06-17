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

#ifndef LE_COMMON_FATAL_ERROR_H
#define LE_COMMON_FATAL_ERROR_H

#include <string>

#include <SDL2/SDL.h>

#if defined __GNUC__
#include <sys/signal.h>
#define LE_HALT_PROGRAM() raise(SIGTRAP);
#elif defined _MSC_VER
#define LE_HALT_PROGRAM() __debugbreak();
#else
#define LE_HALT_PROGRAM()
#endif


#define LE_FATAL_ERROR(msg) \
{ \
  ::LE::detail::display_assert(__FILE__, __FUNCTION__, __LINE__, msg);\
  LE_HALT_PROGRAM(); \
}
#define LE_FATAL_ERROR_IF(cond, msg) { if(cond) { LE_FATAL_ERROR(msg); } }

namespace LE
{

namespace detail
{
  void display_assert(
    std::string const& file,
    std::string const& function,
    int line,
    char const* message);

  void display_assert(
    std::string const& file,
    std::string const& function,
    int line,
    std::string const& message);
}

}

#endif // LE_COMMON_FATAL_ERROR_H