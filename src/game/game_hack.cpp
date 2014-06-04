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

#include "game_hack.h"

#include <graphics/vertex.h>
#include <graphics/vertex_array.h>
#include <graphics/vertex_buffer.h>

namespace LE
{

template<typename comp_t>
class vec2_t
{
public:

  comp_t
};

class transform_component
{
public:
	transform_component();
	~transform_component();
	
private:
};

class graphics_component
{
public:
  graphics_component()
  {
    LE::vertex_array::bind(p_VAO);
    LE::vertex_buffer::bind(GL_ARRAY_BUFFER, p_VBO);

    vertex::specify_vertex_attributes();
    vertex verts[] =
    {
      { { -0.5f, -0.5f }, { 0.0f, 0.0f } },
      { {  0.5f, -0.5f }, { 1.0f, 0.0f } },
      { { -0.5f,  0.5f }, { 0.0f, 1.0f } },

      { { -0.5f,  0.5f }, { 0.0f, 1.0f } },
      { {  0.5f, -0.5f }, { 1.0f, 0.0f } },
      { {  0.5f,  0.5f }, { 1.0f, 1.0f } }
    };
    num_verts = sizeof(verts) / sizeof(vertex);

    LE::vertex_buffer::set_data(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    LE::vertex_array::unbind();
  }

  void bind()
  {
    LE::vertex_array::bind(p_VAO);
  }
   
  void unbind()
  {
    LE::vertex_array::unbind();
  }

  GLsizei get_num_verts() const
  {
    return num_verts;
  }

private:
  LE::vertex_array p_VAO;
  LE::vertex_buffer p_VBO;
  
  GLsizei num_verts = 0;
};

game_hack::game_hack()
{
  
}

void game_hack::update()
{

  graphics_component g_comp;
  LE::vertex_buffer::draw_arrays(GL_TRIANGLES, 0, g_comp.get_num_verts());
}

} // namespace LE
