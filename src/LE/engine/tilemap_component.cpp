/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "tilemap_component.h"

#include <algorithm>


#include <LE/common/char.h>
#include <LE/common/fatal_error.h>
#include <LE/common/logging.h>
#include <LE/common/rapidjson.h>
#include <LE/common/resource_manager.h>
#include <LE/common/resource_exception.h>
#include <LE/graphics/vertex.h>

namespace LE
{

tileset::tileset(std::string const& tsd_file_name)
{
  p_read(tsd_file_name);

  // Calculate vertics and indices for tileset
  std::vector<vertex::pos2_tex2> vertices;
  std::vector<GLuint> indices;

  uvec2 const& texture_dim = p_texture->get_dimensions();
  uvec2 const num_tiles = texture_dim / p_tile_size;
  p_num_tiles = num_tiles.x() * num_tiles.y();

  // Dimensions of a single tile when entire tileset is considered using coordinates [0, 1]
  vec2 const tile_tex_coord_dim = vec2(p_tile_size) / vec2(texture_dim);

  uvec2 curr_tile;
  for(curr_tile.y() = 0; curr_tile.y() < num_tiles.y(); ++curr_tile.y())
  {
    for(curr_tile.x() = 0; curr_tile.x() < num_tiles.x(); ++curr_tile.x())
    {
      // Since size = current max index + 1, the index of the first vertex we add is equal to
      //  the size of the vector before it is added.
      size_t curr_tile_base_vertex = vertices.size();

      // Calculate the texture coordinates for this tile
      vec2 tc_min = vec2(curr_tile) * tile_tex_coord_dim;
      vec2 tc_max = tc_min + tile_tex_coord_dim;

      vertices.emplace_back( vec2{-0.5f, -0.5f}, vec2{tc_min.x(), tc_max.y()} );
      vertices.emplace_back( vec2{ 0.5f, -0.5f}, vec2{tc_max.x(), tc_max.y()} );
      vertices.emplace_back( vec2{ 0.5f,  0.5f}, vec2{tc_max.x(), tc_min.y()} );
      vertices.emplace_back( vec2{-0.5f,  0.5f}, vec2{tc_min.x(), tc_min.y()} );

      GLuint bottom_left_index  = curr_tile_base_vertex + 0;
      GLuint bottom_right_index = curr_tile_base_vertex + 1;
      GLuint top_right_index    = curr_tile_base_vertex + 2;
      GLuint top_left_index     = curr_tile_base_vertex + 3;

      indices.emplace_back(bottom_left_index);
      indices.emplace_back(bottom_right_index);
      indices.emplace_back(top_left_index);

      indices.emplace_back(top_left_index);
      indices.emplace_back(bottom_right_index);
      indices.emplace_back(top_right_index);
    }
  }

  p_tile_vertices.set_data(
    vertices.data(),
    vertices.size(),
    indices.data(),
    indices.size(),
    GL_STATIC_DRAW);
}

void tileset::bind() const
{
  LE_FATAL_ERROR_IF(p_texture->is_valid() == false,
    "Attempting to bind a tileset without a valid texture");

  p_tile_vertices.bind();
  texture2D::bind(*p_texture);
}

void tileset::unbind() const
{
  p_tile_vertices.unbind();
  texture2D::unbind();
}

void tileset::p_read(const std::string & tsd_file_name)
{
  rapidjson::Document doc;
  if(parse_file(doc, tsd_file_name) == false)
  {
    log_error(log_scope::ENGINE, "Unable to create tileset.");

    throw resource_exception{};
  }

  p_texture.reset(
    resource_manager::load<texture2D>(doc["texture"].GetString()) );

  p_tile_size = doc["tile_size"].GetUint();
}

////////////////////

unique_id<engine_component_base> const tilemap_component::type_id;

tilemap_component::tilemap_component(std::string const& tm_file_name)
{
  rapidjson::Document doc;
  if(parse_file(doc, tm_file_name) == false)
  {
    log_error(log_scope::ENGINE, "Unable to create tilemap.");

    throw resource_exception{};
  }

  p_tileset.reset(
    resource_manager::load<tileset>(doc["tileset"].GetString()) );

  p_num_tiles.set(
    doc["width"].GetUint(),
    doc["height"].GetUint());
}

void tilemap_component::bind() const
{
  p_tileset->bind();
}

void tilemap_component::unbind() const
{
  p_tileset->unbind();
}

} // namespace LE
