/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
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
