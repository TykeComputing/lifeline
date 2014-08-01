/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_TILEMAP_COMPONENT_H
#define LE_ENGINE_TILEMAP_COMPONENT_H

#include <memory>

#include <LE/common/unique_id.h>

#include <LE/engine/engine_component_base.h>

#include <LE/graphics/texture.h>
#include <LE/graphics/renderable_array.h>

namespace LE
{

class tilemap_component : public engine_component_base
{
public:
  tilemap_component(texture2D * tileset_texture);

  void bind() const;
  void unbind() const;

  static unique_id<engine_component_base> const type_id;

private:
  renderable_array p_unit_tile;
  std::unique_ptr<texture2D> p_tileset;
};

} // namespace LE

#endif // LE_ENGINE_TILEMAP_COMPONENT_H
