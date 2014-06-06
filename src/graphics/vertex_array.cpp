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

#include "vertex_array.h"

#include <utility>

namespace LE
{

vertex_array::vertex_array()
{
  glGenVertexArrays(1, &p_raw_name);
}

vertex_array::~vertex_array()
{
  glDeleteVertexArrays(1, &p_raw_name);
}

void vertex_array::bind(vertex_array const& VAO)
{
  glBindVertexArray(VAO.p_raw_name);
}

void vertex_array::unbind()
{
  glBindVertexArray(0);
}

} // namespace LE
