/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_TILEMAP_COMPONENT_H
#define LE_ENGINE_TILEMAP_COMPONENT_H

#include <memory>
#include <string>

#include <LE/common/unique_id.h>

#include <LE/engine/engine_component_base.h>

#include <LE/graphics/texture.h>
#include <LE/graphics/renderable_buffer.h>

namespace LE
{

class tileset
{
public:
  /*!
   * \param tsd_file_name Tileset definition file name
   */
  tileset(std::string const& tsd_file_name);

  void bind() const;
  void unbind() const;

  size_t get_tile_size() const { return p_tile_size; }
  size_t get_num_tiles() const { return p_num_tiles; }

private:
  void p_read(std::string const& tsd_file_name);

  renderable_element_buffer p_tile_vertices;
  std::unique_ptr<texture2D> p_texture;

  size_t p_tile_size = 0;
  size_t p_num_tiles = 0;
};

class tilemap_component : public engine_component_base
{
public:
  tilemap_component(std::string const& tm_file_name);

  void bind() const;
  void unbind() const;

  static unique_id<engine_component_base> const type_id;

  tileset const* get_tile_set() const { return p_tileset.get(); }

  uvec2 const& get_num_tiles() const { return p_num_tiles; }

private:
  // TODO: Make resource
  std::unique_ptr<tileset> p_tileset;

  uvec2 p_num_tiles = uvec2::zero;
};

} // namespace LE

#endif // LE_ENGINE_TILEMAP_COMPONENT_H
