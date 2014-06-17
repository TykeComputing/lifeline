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

#include <common/fatal_error.h>

namespace LE
{


debug_drawer_base::debug_drawer_base()
{
  vertex_array::bind(p_VAO);
  vertex_buffer::bind(GL_ARRAY_BUFFER, p_VBO);

  debug_shape_vertex::specify_vertex_attributes();

  vertex_array::unbind();
  vertex_buffer::unbind(GL_ARRAY_BUFFER);
}

debug_drawer_base::~debug_drawer_base()
{
}

bool debug_drawer_base::empty() const
{
  return p_vertices.empty();
}

void debug_drawer_base::clear()
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

  // Draw
  vertex_array::bind(p_VAO);

  vertex_buffer::draw_arrays(mode, 0, p_vertices.size());

  vertex_array::unbind();
}

/**********************************************/
/* debug_line_drawer */
/**********************************************/

void debug_line_drawer::draw()
{
  debug_drawer_base::draw(GL_LINES);
}

void debug_line_drawer::add_line(vec2 const& p0, vec2 const& p1, vec4 const& color)
{
  p_vertices.emplace_back(p0, color);
  p_vertices.emplace_back(p1, color);
}

void debug_line_drawer::add_circle(vec2 const& p, float r, vec4 const& color)
{
  uint const num_subdiv = 16;
  float delta_angle = (pi * 2.0f) / num_subdiv;

  vec2 line_vert_prev_pos = zero_vec2;
  line_vert_prev_pos += p;
  for(uint i = 0; i <= num_subdiv; ++i)
  {
    float angle = i * delta_angle;
    vec2 line_vert_pos({std::cos(angle) * r, std::sin(angle) * r});
    line_vert_pos += p;

    add_line(line_vert_prev_pos, line_vert_pos, color);
    line_vert_prev_pos = line_vert_pos;
  }
}

void debug_line_drawer::add_arrow(vec2 const& p0, vec2 const& norm_dir, float length, vec4 const& color)
{
  LE_FATAL_ERROR_IF(length == 0.0f, "Attempting to draw arrow of length zero!");

  // Arrow body
  vec2 p1 = p0 + (norm_dir * length);
  add_line(p0, p1, color);

  // Arrow head
  float const arrow_head_size_percent = 0.1f;
  float arrow_head_length = min(length * arrow_head_size_percent, 0.25f);

  vec2 orthog_vec_norm = get_orthogonal(norm_dir);

  vec2 arrow_head_end = p1 - (norm_dir * arrow_head_length);

  vec2 orthog_vec = orthog_vec_norm * arrow_head_length * 0.5f;
  add_line(p1, arrow_head_end + orthog_vec, color);
  add_line(p1, arrow_head_end - orthog_vec, color);
}

void debug_line_drawer::add_arrow(vec2 const& p0, vec2 const& v, vec4 const& color)
{
  vec2 v_norm = v;
  float old_len;
  normalize(v_norm, old_len);
  add_arrow(p0, v_norm, old_len, color);
}

void debug_line_drawer::add_aabb(vec2 const& min, vec2 const& max, vec4 const& color)
{
  // (r)ight = max x
  // (t)op   = max y

  // (l)eft    = min x
  // (b)ottom  = min y

  vec2 lt({min[0], max[1]});
  vec2 lb({min[0], min[1]});
  vec2 rb({max[0], min[1]});
  vec2 rt(max);

  // Front
  add_line(lt, lb, color);
  add_line(lb, rb, color);
  add_line(rb, rt, color);
  add_line(rt, lt, color);
}

void debug_line_drawer::add_transform(mat3 const& transform, float scale)
{
  vec2 right({transform(0, 0), transform(1, 0)});
  vec2 up({transform(0, 1), transform(1, 1)});
  vec2 pos({transform(0, 2), transform(1, 2)});

  normalize(right);
  normalize(up);

  add_arrow(pos, right, scale, vec4({1.0f, 0.0f, 0.0f, 1.0f}) );
  add_arrow(pos, up, scale, vec4({0.0f, 1.0f, 0.0f, 1.0f}) );
}

/**********************************************/
/* debug_point_drawer */
/**********************************************/

void debug_point_drawer::draw()
{
  debug_drawer_base::draw(GL_POINTS);
}

void debug_point_drawer::add_point(vec2 const& p, vec4 const& color)
{
  p_vertices.emplace_back(p, color);
}

} // namespace LE
