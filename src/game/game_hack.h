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
#include <unordered_map>
#include <vector>

#include <graphics/shader_program.h>

#include <engine/sprite_component.h>
#include <engine/transform_component.h>

#include <math/vec.h>
#include <math/mat.h>

namespace LE
{

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

  sprite_component m_gfx_comp;
  physics_component_hack m_phx_comp;

  transform_component transform;
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

