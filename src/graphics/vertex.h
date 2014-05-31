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

#ifndef LE_GRAPHICS_VERTEX_H
#define LE_GRAPHICS_VERTEX_H

#include <common/macros.h>

namespace LE
{

// TODO - Consider moving start, num, and end into macro definition.
LE_ENUM_2(vertex_attrib_type,
  position,
  texcoord)

struct vertex
{
  float x, y;
  float s, t;
};

} // namespace LE

#endif // LE_GRAPHICS_VERTEX_H
