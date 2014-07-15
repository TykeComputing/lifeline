/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_GRAPHICS_COMPONENT_H
#define LE_ENGINE_GRAPHICS_COMPONENT_H

#include <GL/glew.h>

#include <common/unique_id.h>

#include <engine/engine_component_base.h>

#include <graphics/texture.h>
#include <graphics/vertex_array.h>
#include <graphics/vertex_buffer.h>

#include <math/vec.h>

namespace LE
{

class sprite_component : public engine_component_base
{
public:
  sprite_component(std::string const& texture_file_name);

  void bind() const;
  void unbind() const;

  GLsizei get_num_verts() const;

  ivec2 get_dimensions() const;

  // TODO: Move and change method of representing colors (RGBA8?)
  vec4 m_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

  static unique_id<engine_component_base> const type_id;
private:
  vertex_array p_VAO;
  vertex_buffer p_VBO;
  texture2D p_texture;

  GLsizei num_verts = 0;
};

} // namespace LE

#endif // LE_ENGINE_GRAPHICS_COMPONENT_H
