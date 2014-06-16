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

#ifndef LE_GRAPHICS_ERROR_CHECKING_H
#define LE_GRAPHICS_ERROR_CHECKING_H

#include <GL/glew.h>

#include <string>

#include <common/fatal_error.h>

#define LE_FATAL_ERROR_IF_GL_ERROR() \
{ \
  GLenum last_error = glGetError(); \
  if(last_error != GL_NO_ERROR) \
  { \
    LE_FATAL_ERROR("Internal OpenGL Error!\nCode(s): " + LE::get_GL_errors(last_error)); \
  } \
}

namespace LE
{

std::string get_GL_errors();
std::string get_GL_errors(GLenum last_error);

}

#endif // LE_GRAPHICS_ERROR_CHECKING_H
