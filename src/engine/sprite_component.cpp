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

sprite_component::sprite_component() :
  p_texture("resources/textures/debug/linear_ramp.png")
{
  auto const texture_dim = p_texture.get_dimensions();
  float const texture_half_x = texture_dim.x() / 2.0f;
  float const texture_half_y = texture_dim.y() / 2.0f;

  vertex_array::bind(p_VAO);
  vertex_buffer::bind(GL_ARRAY_BUFFER, p_VBO);

  vertex::specify_vertex_attributes();
  vertex verts[] =
  {
    { vec2mk(-texture_half_x, -texture_half_y), vec2mk(0.0f, 1.0f) },
    { vec2mk( texture_half_x, -texture_half_y), vec2mk(1.0f, 1.0f) },
    { vec2mk(-texture_half_x,  texture_half_y), vec2mk(0.0f, 0.0f) },

    { vec2mk(-texture_half_x,  texture_half_y), vec2mk(0.0f, 0.0f) },
    { vec2mk( texture_half_x, -texture_half_y), vec2mk(1.0f, 1.0f) },
    { vec2mk( texture_half_x,  texture_half_y), vec2mk(1.0f, 0.0f) }
  };
  num_verts = sizeof(verts) / sizeof(vertex);

  vertex_buffer::set_data(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

  vertex_array::unbind();
}

sprite_component::sprite_component(vec4 const& color) :
  sprite_component()
{
  m_color = color;
}

void sprite_component::bind() const
{
  vertex_array::bind(p_VAO);
  texture2D::bind(p_texture);
}

void sprite_component::unbind() const
{
  texture2D::unbind();
  vertex_array::unbind();
}

GLsizei sprite_component::get_num_verts() const
{
  return num_verts;
}

ivec2 sprite_component::get_dimensions() const
{
  return p_texture.get_dimensions();
}

} // namespace LE
