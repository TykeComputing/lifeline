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

#include <memory>
#include <vector>

#include <graphics/vertex.h>
#include <graphics/vertex_array.h>
#include <graphics/vertex_buffer.h>

#include <graphics/shader_program.h>

namespace LE
{
  
//////////////////////////////////////////////////////////////////////////
template<typename comp_t>
class vec4_t
{
public:
  vec4_t()
  {
    // Do nothing
  }
  
  vec4_t(comp_t x, comp_t y, comp_t z, comp_t w) :
    x(x), y(y), z(z), w(w)
  {
  }

  static size_t const num_components = 4;

  union
  {
    struct
    {
      comp_t x, y, z, w;
    };
    struct
    {
      comp_t r, g, b, a;
    };

    comp_t v[num_components];
  };
};

typedef vec4_t<float> vec4;

//////////////////////////////////////////////////////////////////////////
template<typename comp_t>
class vec2_t
{
public:
  vec2_t()
  {
    // Do nothing
  }

  vec2_t(comp_t x, comp_t y) :
    x(x), y(y)
  {
  }

  static size_t const num_components = 2;

  union
  {
     struct
     {
       comp_t x, y;
     }; 
     struct
     {
       comp_t s, t;
     };
    
    comp_t v[num_components];
  };
};

typedef vec2_t<float> vec2;

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

//////////////////////////////////////////////////////////////////////////
class graphics_component_hack
{
public:
  graphics_component_hack();
  graphics_component_hack(vec4 const& color);
  graphics_component_hack(vec4 && color);

  void bind() const;
  void unbind() const;

  GLsizei get_num_verts() const;

  vec4 m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
private:
  LE::vertex_array p_VAO;
  LE::vertex_buffer p_VBO;

  GLsizei num_verts = 0;
};

//////////////////////////////////////////////////////////////////////////
class entity_hack
{
public:
  entity_hack(std::string const& name, float health, vec4 const& color,  vec2 const& pos, vec2 const& scale);
  entity_hack(std::string && name, float health, vec4 && color, vec2 && pos, vec2 && scale);

  graphics_component_hack m_g_comp;
  vec2 m_pos;
  vec2 m_scale;
  float m_health;
  std::string m_name;
};

class engine;

class game_hack
{
public:
  game_hack(engine & game_engine);
  ~game_hack();

  void update();

  void kill_entity(std::unique_ptr<entity_hack> const& enemy);

private:
  std::vector<std::unique_ptr<entity_hack>> p_entities;
  std::unique_ptr<shader_program> p_shader_prog;
};

} // namespace LE

#endif // LE_GAME_GAME_HACK_H
