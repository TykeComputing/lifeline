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
#include <LE/graphics/renderable_array.h>

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

private:

  // TODO: Make resource
  std::unique_ptr<texture2D> p_texture;
};

class tilemap_component : public engine_component_base
{
public:
  tilemap_component(tileset * new_tileset);

  void bind() const;
  void unbind() const;

  static unique_id<engine_component_base> const type_id;

private:
  renderable_array p_unit_tile;
  // TODO: Make resource
  std::unique_ptr<tileset> p_tileset;
};

} // namespace LE

#endif // LE_ENGINE_TILEMAP_COMPONENT_H
