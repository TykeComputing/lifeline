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

  void set(comp_t new_x, comp_t new_y, comp_t new_z, comp_t new_w)
  {
    x = new_x;
    y = new_y;
    z = new_z;
    w = new_w;
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

  void set(comp_t new_x, comp_t new_y)
  {
    x = new_x;
    y = new_y;
  }

  vec2_t<comp_t> operator+(vec2_t<comp_t> const& rhs)
  {
    return {
      x + rhs.x,
      y + rhs.y
    };
  }

  vec2_t<comp_t> const& operator+=(vec2_t<comp_t> const& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  vec2_t<comp_t> operator-(vec2_t<comp_t> const& rhs)
  {
    return {
      x - rhs.x,
      y - rhs.y
    };
  }

  vec2_t<comp_t> const& operator-=(vec2_t<comp_t> const& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  vec2_t<comp_t> operator*(comp_t rhs)
  {
    return {
      x * rhs,
      y * rhs
    };
  }

  vec2_t<comp_t> const& operator*=(comp_t rhs)
  {
    x *= rhs;
    y *= rhs;
    return *this;
  }

  vec2_t<comp_t> operator/(comp_t rhs)
  {
    return {
      x / rhs,
      y / rhs
    };
  }

  vec2_t<comp_t> const& operator/=(comp_t rhs)
  {
    x /= rhs;
    y /= rhs;
    return *this;
  }

  comp_t get_length() const
  {
    return std::sqrt(get_length_sq());
  }

  comp_t get_length_sq() const
  {
    return dot(*this, *this);
  }

  // Returns old length
  comp_t normalize()
  {
    comp_t length = get_length();
    x /= length;
    y /= length;

    return length;
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

template<typename comp_t>
float dot(vec2_t<comp_t> const& lhs, vec2_t<comp_t> const& rhs)
{
  return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}

template<typename comp_t>
float get_length(vec2_t<comp_t> const& lhs)
{
  return lhs.get_length();
}

template<typename comp_t>
float get_length_sq(vec2_t<comp_t> const& lhs)
{
  return lhs.get_length_sq();
}

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

  vec4 m_color = { 1.0f, 1.0f, 1.0f, 1.0f }; // TODO: Move and change method of representing colors (RGBA8?)
private:
  vertex_array p_VAO;
  vertex_buffer p_VBO;

  GLsizei num_verts = 0;
};

//////////////////////////////////////////////////////////////////////////
class physics_component_hack
{
public:
  vec2 m_velocity = { 0.0f, 0.0f };
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
  entity_hack(std::string const& name);
  entity_hack(char const* name);

  graphics_component_hack m_gfx_comp;
  physics_component_hack m_phx_comp;

  vec2 m_pos = { 0.0f, 0.0f };
  vec2 m_scale = { 0.1f, 0.1f };
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

  game_hack(engine & game_engine);
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
