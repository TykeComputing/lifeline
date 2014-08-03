/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "tilemap_component.h"

#include <algorithm>

#include <rapidjson/document.h>
#include <rapidjson/filestream.h>

#include <LE/common/char.h>
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
  p_read(tsd_file_name);

  // Calculate vertics and indices for tileset
  std::vector<vertex::pos2_tex2> vertices;
  std::vector<GLuint> indices;

  uvec2 const& texture_dim = p_texture->get_dimensions();
  uvec2 const num_tiles = texture_dim / p_tile_size;

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
      vec2 tc_max = tc_max + tile_tex_coord_dim;

      vertices.emplace_back( vec2{-0.5f, -0.5f}, vec2{tc_min.x(), tc_max.y()} );
      vertices.emplace_back( vec2{ 0.5f, -0.5f}, vec2{tc_max.x(), tc_max.y()} );
      vertices.emplace_back( vec2{ 0.5f,  0.5f}, vec2{tc_max.x(), tc_min.y()} );
      vertices.emplace_back( vec2{-0.5f,  0.5f}, vec2{tc_min.x(), tc_min.y()} );

      GLuint bottom_left_index  = curr_tile_base_vertex + 0;
      GLuint bottom_right_index = curr_tile_base_vertex + 1;
      GLuint top_left_index     = curr_tile_base_vertex + 2;
      GLuint top_right_index    = curr_tile_base_vertex + 3;

      indices.emplace_back(bottom_left_index);
      indices.emplace_back(bottom_right_index);
      indices.emplace_back(top_left_index);

      indices.emplace_back(top_right_index);
      indices.emplace_back(bottom_left_index);
      indices.emplace_back(bottom_right_index);
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

  texture2D::bind(*p_texture);
}

void tileset::unbind() const
{
  texture2D::unbind();
}

void tileset::p_read(const std::string & tsd_file_name)
{
  file_string tsd_file_data(tsd_file_name);
  if(tsd_file_data.is_valid() == false)
  {
    log_error(log_scope::ENGINE,
      "Unable to open tileset definition file \"{}\".", tsd_file_name);

    throw resource_exception{};
  }

  rapidjson::Document tsd_doc;
  tsd_doc.Parse<0>(tsd_file_data.get_str().c_str());
  if(tsd_doc.HasParseError())
  {
    // rapidjson does not provide line/column, only character offset
    //   hacking it here until (if) rapidjson implements it
    // TODO - Move to function elsewhere
    std::string const& tsd_file_str = tsd_file_data.get_str();
    size_t const error_char_offset = tsd_doc.GetErrorOffset();
    std::string::const_iterator error_it =
      tsd_file_str.cbegin() + error_char_offset;

    // Compute line number, using 1 as base line
    size_t const error_line_num = 1 + std::count_if(
      tsd_file_str.cbegin(),
      error_it,
      is_newline);

    // Compute column (char offset into line), using 1 as base column
    std::string::const_reverse_iterator reverse_error_it{error_it};
    auto error_line_begin_it = std::find(
      reverse_error_it,
      tsd_file_str.crend(),
      '\n');

      // If this is the first line we can
    size_t const error_column_num =
      error_line_begin_it != tsd_file_str.crend()
        ? std::distance(reverse_error_it, error_line_begin_it) + 1
        : error_char_offset + 1;

    // Log error
    log_error(log_scope::ENGINE, "Error parsing tilemap definition file {}", tsd_file_name);
    log_error_no_prefix(log_line_seperator);
    log_error_no_prefix("== JSON ERRORS ==========");
    log_error_no_prefix("Line {}, Column {} - {}",
      error_line_num,
      error_column_num,
      tsd_doc.GetParseError());
    log_error_no_prefix(log_line_seperator);

    throw resource_exception{};
  }

  p_texture.reset(
    resource_manager::load<texture2D>(tsd_doc["texture_name"].GetString()) );

  p_tile_size = tsd_doc["tile_size"].GetUint();
}

////////////////////

unique_id<engine_component_base> const tilemap_component::type_id;

tilemap_component::tilemap_component(tileset * new_tileset) :
  p_tileset(new_tileset)
{

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
