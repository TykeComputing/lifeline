/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_GRAPHICS_COMPONENT_H
#define LE_ENGINE_GRAPHICS_COMPONENT_H

#include <memory>

#include <GL/glew.h>

#include <LE/common/unique_id.h>

#include <LE/engine/engine_component_base.h>

#include <LE/graphics/texture.h>
#include <LE/graphics/renderable_buffer.h>

#include <LE/math/vec.h>

namespace LE
{

class sprite_component : public engine_component_base
{
public:
  sprite_component(texture2D * new_texture);

  // NOTE: Sprite assumes ownership of texture
  // TODO - Remove note when resources are implemented
  void set_texture(texture2D * texture);

  void bind() const;
  void unbind() const;

  GLsizei get_num_verts() const;

  uvec2 get_dimensions() const;

  // TODO: Move and change method of representing colors (RGBA8?)
  vec4 m_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

  static unique_id<engine_component_base> const type_id;

private:
  void p_set_buffer_data();

  // TODO - Make resource (unique ptr to emulate interface, but will involve extra destructions
  //          and construtions.
  std::unique_ptr<texture2D> p_texture;
  renderable_array_buffer p_quad;
};

} // namespace LE

#endif // LE_ENGINE_GRAPHICS_COMPONENT_H
