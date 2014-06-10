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

#ifndef LE_GAME_GAME_HACK_H
#define LE_GAME_GAME_HACK_H

#include <cmath>
#include <memory>
#include <unordered_map>
#include <vector>

#include <graphics/shader_program.h>
#include <graphics/vertex.h>
#include <graphics/vertex_array.h>
#include <graphics/vertex_buffer.h>

#include <math/vec.h>
#include <math/mat.h>

namespace LE
{

//template<typename comp_t, size_t comp_n>
//////////////////////////////////////////////////////////////////////////

#if defined __GNUC__

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"

#elif defined _MSC_VER

#pragma warning( push )
#pragma warning( disable : 4201 )

#endif

//////////////////////////////////////////////////////////////////////////
template<typename comp_t>
class mat3_t
{
public:

  static size_t const num_rows = 3;
  static size_t const num_columns = 3;
  static size_t const num_components = num_rows * num_columns;

  mat3_t(comp_t m00, comp_t m01, comp_t m02,
         comp_t m10, comp_t m11, comp_t m12,
         comp_t m20, comp_t m21, comp_t m22)
    : m00(m00), m01(m01), m02(m02),
      m10(m10), m11(m11), m12(m12),
      m20(m20), m21(m21), m22(m22)
  {
  }

  union
  {
    struct
    {
      comp_t m00, m01, m02,
             m10, m11, m12,
             m20, m21, m22;
    };

    comp_t a[num_components];
    comp_t m[num_rows][num_columns];
  };
};

typedef mat3_t<float> mat3;

#if defined __GNUC__
#pragma GCC diagnostic pop
#elif defined _MSC_VER
#pragma warning( pop )
#endif

//////////////////////////////////////////////////////////////////////////
class graphics_component_hack
{
public:
  graphics_component_hack();
  explicit graphics_component_hack(vec4 const& color);
  graphics_component_hack(vec4 && color);

  void bind() const;
  void unbind() const;

  GLsizei get_num_verts() const;

  vec4 m_color = vec4({ 1.0f, 1.0f, 1.0f, 1.0f }); // TODO: Move and change method of representing colors (RGBA8?)
private:
  vertex_array p_VAO;
  vertex_buffer p_VBO;

  GLsizei num_verts = 0;
};

//////////////////////////////////////////////////////////////////////////
class physics_component_hack
{
public:
  vec2 m_velocity = vec2({ 0.0f, 0.0f });
};

//////////////////////////////////////////////////////////////////////////
typedef unsigned unique_id_t;

struct unique_id_gen
{
  unique_id_t generate()
  {
    static unique_id_t curr_id = 1;
    return curr_id++;
  }
};

//////////////////////////////////////////////////////////////////////////
class entity_hack
{
public:
  explicit entity_hack(std::string const& name);
  explicit entity_hack(char const* name);

  graphics_component_hack m_gfx_comp;
  physics_component_hack m_phx_comp;

  vec2 m_pos = vec2({ 0.0f, 0.0f });
  vec2 m_scale = vec2({ 0.1f, 0.1f });
  float m_health = 100.0f;
  std::string m_name = "unnamed";
  unique_id_t m_id;
};

//////////////////////////////////////////////////////////////////////////
template<typename T>
bool operator==(std::unique_ptr<T> const& lhs, T const* rhs)
{
  return lhs.get() == rhs;
}

//////////////////////////////////////////////////////////////////////////
class engine;

class game_hack
{
public:
  //typedef std::shared_ptr<entity_hack> entity_owning_ptr;
  //typedef std::weak_ptr<entity_hack> entity_borrowed_ptr;

  explicit game_hack(engine & game_engine);
  ~game_hack();

  std::weak_ptr<entity_hack> create_entity(std::string const& name);
  std::weak_ptr<entity_hack> find_entity(std::string const& name);
  void kill_entity(std::weak_ptr<entity_hack> target);

  bool update(float dt);
  void draw();

private:
  std::unordered_map<unique_id_t, std::shared_ptr<entity_hack>> p_entities;
  std::unique_ptr<shader_program> p_shader_prog;
};

} // namespace LE

#endif // LE_GAME_GAME_HACK_H

