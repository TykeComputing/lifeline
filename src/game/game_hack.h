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

#include <engine/engine.h>
#include <engine/space.h>

#include <graphics/debug_drawer.h>
#include <graphics/shader_program.h>

#include <math/vec.h>
#include <math/mat.h>

namespace LE
{

//////////////////////////////////////////////////////////////////////////
class physics_component_hack
{
public:
  vec2 m_velocity = zero_vec2;
};

//////////////////////////////////////////////////////////////////////////
class engine;

class game_hack
{
public:
  explicit game_hack(engine & game_engine, space & game_space);
  ~game_hack();

  void load_shader(
    engine & game_engine,
    std::unique_ptr<shader_program> & out_sp,
    char const* vert,
    char const* frag);

  bool update(space & game_space, float dt);
  void draw(space & game_space);

private:
  std::unique_ptr<shader_program> p_shader_prog;
  std::unique_ptr<shader_program> p_debug_shader_prog;
  debug_line_drawer p_line_drawer;
  debug_point_drawer p_point_drawer;
};

} // namespace LE

#endif // LE_GAME_GAME_HACK_H
