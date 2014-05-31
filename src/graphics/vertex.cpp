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

#include "vertex.h"

#include <cstddef> // offsetof

#include <graphics/vertex_buffer.h>

namespace LE
{

void vertex::specify_vertex_attributes()
{
  vertex_buffer::specify_vertex_attrtibute(
    vertex_attrib_type::position,
    decltype(position)::num_components, GL_FLOAT, GL_FALSE,
    sizeof(vertex), offsetof(vertex, position));

  vertex_buffer::specify_vertex_attrtibute(
    vertex_attrib_type::texcoord,
    decltype(texcoord)::num_components, GL_FLOAT, GL_FALSE,
    sizeof(vertex), offsetof(vertex, texcoord));
}

} // namespace LE
