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

#ifndef LE_GRAPHICS_VERTEX_ARRAY_H
#define LE_GRAPHICS_VERTEX_ARRAY_H

#include <GL/glew.h>

#include <common/macros.h>

namespace LE
{

class vertex_array
{
public:
  LE_NON_COPYABLE(vertex_array)

  vertex_array();
  ~vertex_array();

  static void bind(vertex_array const& VAO);
  static void unbind();

private:
  GLuint p_raw_name = 0;
};

} // namespace LE

#endif // LE_GRAPHICS_VERTEX_ARRAY_H
