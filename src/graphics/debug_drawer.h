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

#ifndef LE_GRAPHICS_DEBUG_SHAPE_DRAWER_H
#define LE_GRAPHICS_DEBUG_SHAPE_DRAWER_H

#include <vector>

#include <common/macros.h>

#include <graphics/vertex_array.h>
#include <graphics/vertex_buffer.h>
#include <graphics/vertex.h>

namespace LE
{

/*
 * Base class for debug drawers.
 *
 * NOTE - Debug drawers must be manually cleared once per draw.
 */
class debug_drawer_base
{
public:
  LE_NON_COPYABLE(debug_drawer_base)

  bool empty() const;

  void clear();

  void reserve(unsigned amount);

protected:
  debug_drawer_base();
  virtual ~debug_drawer_base();

  std::vector<debug_shape_vertex> p_vertices;

  void draw(GLenum prim_mode);

private:
  vertex_array p_VAO;
  vertex_buffer p_VBO;

  void _aquire_buffer();
  void _release_buffer();
};

class debug_line_drawer : public debug_drawer_base
{
public:
  void draw();

  void add_line(vec2 const& p0, vec2 const& p1, vec4 const& color);
};

class debug_point_drawer : public debug_drawer_base
{
public:
  void draw();

  void add_point(vec2 const& p0, vec4 const& color);
};

} // namespace LE

#endif // LE_GRAPHICS_DEBUG_SHAPE_DRAWER_H
