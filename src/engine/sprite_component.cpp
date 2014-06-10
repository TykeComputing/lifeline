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

#include "sprite_component.h"

#include <graphics/vertex.h>

namespace LE
{

sprite_component::sprite_component()
{
  LE::vertex_array::bind(p_VAO);
  LE::vertex_buffer::bind(GL_ARRAY_BUFFER, p_VBO);

  vertex::specify_vertex_attributes();
  vertex verts[] =
  {
    { vec2({ -0.5f, -0.5f }), vec2({ 0.0f, 0.0f }) },
    { vec2({  0.5f, -0.5f }), vec2({ 1.0f, 0.0f }) },
    { vec2({ -0.5f,  0.5f }), vec2({ 0.0f, 1.0f }) },

    { vec2({ -0.5f,  0.5f }), vec2({ 0.0f, 1.0f }) },
    { vec2({  0.5f, -0.5f }), vec2({ 1.0f, 0.0f }) },
    { vec2({  0.5f,  0.5f }), vec2({ 1.0f, 1.0f }) }
  };
  num_verts = sizeof(verts) / sizeof(vertex);

  LE::vertex_buffer::set_data(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

  LE::vertex_array::unbind();
}

sprite_component::sprite_component(vec4 const& color) :
  sprite_component()
{
  m_color = color;
}

void sprite_component::bind() const
{
  LE::vertex_array::bind(p_VAO);
}

void sprite_component::unbind() const
{
  LE::vertex_array::unbind();
}

GLsizei sprite_component::get_num_verts() const
{
  return num_verts;
}

} // namespace LE
