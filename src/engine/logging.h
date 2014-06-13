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

#ifndef LE_ENGINE_LOGGING_H
#define LE_ENGINE_LOGGING_H

#include <common/logging.h>

namespace LE
{

template<typename... Ts>
void log_engine_status(char const* format, Ts const&... vs)
{
  log_status("engine", format, vs...);
}

template<typename... Ts>
void log_engine_error(char const* format, Ts const&... vs)
{
  log_error("engine", format, vs...);
}

}

#endif // LE_ENGINE_LOGGING_H
