/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_TILEMAP_COMPONENT_H
#define LE_ENGINE_TILEMAP_COMPONENT_H

#include <memory>
#include <string>
#include <vector>

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

  size_t get_tile_index_buffer_offset(size_t tile_index) const;
  static size_t num_indices_per_tile() { return 6; }

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
  typedef int tile_id_t;

  tilemap_component(std::string const& tm_file_name);

  void bind() const;
  void unbind() const;

  static unique_id<engine_component_base> const type_id;

  tileset const* get_tile_set() const { return p_tileset.get(); }
  uvec2 const& get_num_tiles() const { return p_num_tiles; }
  size_t count_num_tile_id_instances(tile_id_t value) const;

  tile_id_t get_tile_id(unsigned x, unsigned y) const;
  void set_tile_id(unsigned x, unsigned y, tile_id_t value);

  tile_id_t try_get_tile_id(unsigned x, unsigned y) const;
  void try_set_tile_id(unsigned x, unsigned y, tile_id_t value);

  static bool tile_exists(tile_id_t value) { return value >= 0; }

private:
  unsigned p_get_tile_index(unsigned x, unsigned y) const;

  // TODO: Make resource
  std::unique_ptr<tileset> p_tileset;
  uvec2 p_num_tiles = uvec2::zero;
  std::vector<tile_id_t> p_tiles;
};

} // namespace LE

#endif // LE_ENGINE_TILEMAP_COMPONENT_H
