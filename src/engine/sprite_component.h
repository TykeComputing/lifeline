/*
************************************************************************************************
Copyright 2014 Peter Clark

This file is part of Lifeline Engine.

Lifeline Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Lifeline Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Lifeline Engine.  If not, see <http://www.gnu.org/licenses/>.
************************************************************************************************
*/

#ifndef LE_ENGINE_GRAPHICS_COMPONENT_H
#define LE_ENGINE_GRAPHICS_COMPONENT_H

#include <GL/glew.h>

#include <common/unique_id.h>

#include <graphics/vertex_array.h>
#include <graphics/vertex_buffer.h>

#include <math/vec.h>

#include <engine/component_base.h>

namespace LE
{

class sprite_component : public component_base
{
public:
  sprite_component();
  explicit sprite_component(vec4 const& color);

  void bind() const;
  void unbind() const;

  GLsizei get_num_verts() const;

  vec4 m_color = vec4({ 1.0f, 1.0f, 1.0f, 1.0f }); // TODO: Move and change method of representing colors (RGBA8?)

  static unique_id<component_base> const type_id;
private:
  vertex_array p_VAO;
  vertex_buffer p_VBO;

  GLsizei num_verts = 0;
};

} // namespace LE

#endif // LE_ENGINE_GRAPHICS_COMPONENT_H
