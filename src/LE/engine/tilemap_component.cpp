/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "tilemap_component.h"

#include <rapidjson/document.h>
#include <rapidjson/filestream.h>

#include <LE/common/file_string.h>
#include <LE/common/fatal_error.h>
#include <LE/common/resource_manager.h>
#include <LE/common/resource_exception.h>
#include <LE/graphics/vertex.h>

namespace LE
{

tileset::tileset(std::string const& tileset_definition_file_name)
{
  file_string tilest_definition_file_data(tileset_definition_file_name)
  rapidjson::Document

  std::string tileset_texture_file_name;
  p_texture.swap(texture2D());
}

////////////////////

unique_id<engine_component_base> const tilemap_component::type_id;

tilemap_component::tilemap_component(tileset * new_tileset) :
  p_tileset(new_tileset)
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
