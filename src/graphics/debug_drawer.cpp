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

#include "debug_drawer.h"

namespace LE
{


debug_drawer_base::debug_drawer_base(void)
{
  vertex_array::bind(p_VAO);
  vertex_buffer::bind(GL_ARRAY_BUFFER, p_VBO);

  debug_shape_vertex::specify_vertex_attributes();

  vertex_array::unbind();
  vertex_buffer::unbind(GL_ARRAY_BUFFER);
}

debug_drawer_base::~debug_drawer_base(void)
{
}

bool debug_drawer_base::empty(void) const
{
  return p_vertices.empty();
}

void debug_drawer_base::clear(void)
{
  p_vertices.clear();
}

void debug_drawer_base::reserve(unsigned amount)
{
  p_vertices.reserve(p_vertices.size() + amount);
}

void debug_drawer_base::draw(GLenum mode)
{
  if(p_vertices.empty())
    return;

  // Set data
  // TODO - Reconsider doing this here, leftover from old implementation
  vertex_array::unbind();

  vertex_buffer::bind(GL_ARRAY_BUFFER, p_VBO);
  vertex_buffer::set_data(
    GL_ARRAY_BUFFER,
    p_vertices.size() * sizeof(debug_shape_vertex),
    p_vertices.data(),
    GL_STREAM_DRAW);
  vertex_buffer::unbind(GL_ARRAY_BUFFER);

  clear();

  // Draw
  vertex_array::bind(p_VAO);

  vertex_buffer::draw_arrays(mode, 0, p_vertices.size());

  vertex_array::unbind();
}

/**********************************************/
/* debug_line_drawer */
/**********************************************/

void debug_line_drawer::draw(void)
{
  debug_drawer_base::draw(GL_LINES);
}

void debug_line_drawer::add_line(vec2 const& p0, vec2 const& p1, vec4 const& color)
{
  p_vertices.emplace_back(p0, color);
  p_vertices.emplace_back(p1, color);
}

/**********************************************/
/* debug_point_drawer */
/**********************************************/

void debug_point_drawer::draw(void)
{
  debug_drawer_base::draw(GL_POINTS);
}

void debug_point_drawer::add_point(vec2 const& p, vec4 const& color)
{
  p_vertices.emplace_back(p, color);
}

} // namespace LE
