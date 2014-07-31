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
#include <LE/graphics/vertex_array.h>
#include <LE/graphics/vertex_buffer.h>

namespace LE
{

class tilemap_component : public engine_component_base
{
public:
  tilemap_component();
  virtual ~tilemap_component() {}

  static unique_id<engine_component_base> const type_id;

private:
  vertex_array p_VAO;
  vertex_buffer p_VBO;

  std::unique_ptr<texture> p_tileset;
};

} // namespace LE

#endif // LE_ENGINE_TILEMAP_COMPONENT_H
