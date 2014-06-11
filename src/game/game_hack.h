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

#include <math/vec.h>
#include <math/mat.h>

#include <engine/entity.h>

namespace LE
{

//////////////////////////////////////////////////////////////////////////
class physics_component_hack
{
public:
  vec2 m_velocity = vec2({ 0.0f, 0.0f });
};

//////////////////////////////////////////////////////////////////////////
class engine;

class game_hack
{
public:
  //typedef std::shared_ptr<entity> entity_owning_ptr;
  //typedef std::weak_ptr<entity> entity_borrowed_ptr;

  explicit game_hack(engine & game_engine);
  ~game_hack();

  bool update(float dt);
  void draw();

private:
  std::unique_ptr<shader_program> p_shader_prog;
};

} // namespace LE

#endif // LE_GAME_GAME_HACK_H
