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

#include "error_checking.h"

namespace LE
{

std::string get_GL_errors()
{
  return get_GL_errors(glGetError());
}

std::string get_GL_errors(GLenum last_error)
{
  std::string error_string;
  while(last_error != GL_NO_ERROR)
  {
    error_string += std::to_string(last_error);

    last_error = glGetError();

    if(last_error != GL_NO_ERROR)
    {
      error_string.append(", ");
    }
  }
  return error_string;
}

} // namespace LE
