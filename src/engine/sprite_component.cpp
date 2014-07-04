/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "sprite_component.h"

#include <graphics/vertex.h>

namespace LE
{

unique_id<component_base> const sprite_component::type_id;

sprite_component::sprite_component()
{
  LE::vertex_array::bind(p_VAO);
  LE::vertex_buffer::bind(GL_ARRAY_BUFFER, p_VBO);

  vertex::specify_vertex_attributes();
  vertex verts[] =
  {
    { vec2mk(-0.5f, -0.5f), vec2mk(0.0f, 0.0f) },
    { vec2mk( 0.5f, -0.5f), vec2mk(1.0f, 0.0f) },
    { vec2mk(-0.5f,  0.5f), vec2mk(0.0f, 1.0f) },

    { vec2mk(-0.5f,  0.5f), vec2mk(0.0f, 1.0f) },
    { vec2mk( 0.5f, -0.5f), vec2mk(1.0f, 0.0f) },
    { vec2mk( 0.5f,  0.5f), vec2mk(1.0f, 1.0f) }
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
