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
#include <LE/common/logging.h>
#include <LE/common/resource_manager.h>
#include <LE/common/resource_exception.h>
#include <LE/graphics/vertex.h>

namespace LE
{

tileset::tileset(std::string const& tsd_file_name)
{
  file_string tsd_file_data(tsd_file_name);
  if(tsd_file_data.is_valid() == false)
  {
    throw resource_exception(
      "Unable to open tileset definition file \"" + tsd_file_name + "\".");
  }

  rapidjson::Document tsd_doc;
  tsd_doc.Parse<0>(tsd_file_data.get_str().c_str());
  if(tsd_doc.HasParseError())
  {
    log_error(log_scope::ENGINE, "Error parsing tilemap definition file {}", tsd_file_name);
    log_error_no_prefix(log_line_seperator);
    log_error_no_prefix("== JSON ERRORS ==========");
    log_error_no_prefix("{}", tsd_doc.GetParseError());
    log_error_no_prefix(log_line_seperator);
    return;
  }

  std::string ts_texture_file_name = tsd_doc["texture_name"].GetString();

  p_texture.reset(new texture2D(ts_texture_file_name));
}

void tileset::bind() const
{
  LE_FATAL_ERROR_IF(p_texture->is_valid() == false,
    "Attempting to bind sprite without a valid texture");

  texture2D::bind(*p_texture);
}

void tileset::unbind() const
{
  texture2D::unbind();
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
  p_unit_tile.bind();
  p_tileset->bind();
}

void tilemap_component::unbind() const
{
  p_tileset->unbind();
  p_unit_tile.unbind();
}

} // namespace LE
