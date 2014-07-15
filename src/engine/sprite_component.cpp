/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "sprite_component.h"

#include <common/fatal_error.h>
#include <common/resource_manager.h>

#include <graphics/vertex.h>

namespace LE
{

unique_id<engine_component_base> const sprite_component::type_id;

sprite_component::sprite_component(texture2D * texture) :
  p_texture(texture)
{
  p_set_buffer_data();
}

// NOTE: Sprite assumes ownership of texture
// TODO - Remove note when resources are implemented
void sprite_component::set_texture(texture2D * texture)
{
  p_texture.reset(texture);

  if(texture != nullptr)
  {
    p_set_buffer_data();
  }
}

void sprite_component::bind() const
{
  LE_FATAL_ERROR_IF(p_texture->is_valid() == false,
    "Attempting to bind sprite without a valid texture");

  vertex_array::bind(p_VAO);
  texture2D::bind(*p_texture);
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
  return p_texture->get_dimensions();
}

void sprite_component::p_set_buffer_data()
{
  if(p_texture == nullptr)
  {
    return;
  }

  auto const texture_dim = p_texture->get_dimensions();
  float const texture_half_x = texture_dim.x() * 0.5f;
  float const texture_half_y = texture_dim.y() * 0.5f;

  vertex_array::bind(p_VAO);
  vertex_buffer::bind(GL_ARRAY_BUFFER, p_VBO);

  vertex::specify_vertex_attributes();
  vertex verts[] =
  {
    { vec2(-texture_half_x, -texture_half_y), vec2(0.0f, 1.0f) },
    { vec2( texture_half_x, -texture_half_y), vec2(1.0f, 1.0f) },
    { vec2(-texture_half_x,  texture_half_y), vec2(0.0f, 0.0f) },

    { vec2(-texture_half_x,  texture_half_y), vec2(0.0f, 0.0f) },
    { vec2( texture_half_x, -texture_half_y), vec2(1.0f, 1.0f) },
    { vec2( texture_half_x,  texture_half_y), vec2(1.0f, 0.0f) }
  };
  num_verts = sizeof(verts) / sizeof(vertex);

  vertex_buffer::set_data(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

  vertex_array::unbind();
}

} // namespace LE
