/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "tilemap_component.h"

#include <LE/common/fatal_error.h>
#include <LE/graphics/vertex.h>

namespace LE
{

unique_id<engine_component_base> const tilemap_component::type_id;

tilemap_component::tilemap_component(texture2D * tileset_texture) :
  p_tileset(tileset_texture)
{
  vertex::pos2 verts[] =
  {
    { vec2(-0.5f, -0.5f) },
    { vec2( 0.5f, -0.5f) },
    { vec2(-0.5f,  0.5f) },

    { vec2(-0.5f,  0.5f) },
    { vec2( 0.5f, -0.5f) },
    { vec2( 0.5f,  0.5f) }
  };
  size_t num_verts = sizeof(verts) / sizeof(vertex::pos2_tex2);

  p_unit_tile.set_data(verts, num_verts, GL_STATIC_DRAW);
}

void tilemap_component::bind() const
{
  LE_FATAL_ERROR_IF(p_tileset->is_valid() == false,
    "Attempting to bind sprite without a valid texture");

  p_unit_tile.bind();
  texture2D::bind(*p_tileset);
}

void tilemap_component::unbind() const
{
  texture2D::unbind();
  p_unit_tile.unbind();
}

} // namespace LE
