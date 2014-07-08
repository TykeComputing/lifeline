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

#include <devui/perf_vis.h>

#include <engine/component_base.h>
#include <engine/space.h>
#include <engine/sprite_component.h>

#include <graphics/debug_draw_manager.h>
#include <graphics/shader_program.h>

#include <math/vec.h>
#include <math/mat.h>

namespace LE
{

//////////////////////////////////////////////////////////////////////////
//class sprite_text_component_hack : public component_base
//{
//  //sprite_text_component_hack();
//  sprite_text_component_hack()
//  {

//  }

//  sprite_component p_sprite;
//};

//////////////////////////////////////////////////////////////////////////
class engine;

class game_hack
{
public:
  explicit game_hack(engine & game_engine, space & game_space);
  ~game_hack();

  void load_shader(
    std::unique_ptr<shader_program> & out_sp,
    char const* vert,
    char const* frag);

  bool input(space & game_space, float dt);
  void logic(space & game_space, float dt);
  void physics(space & game_space, float dt);
  bool update(space & game_space, float dt);
  void draw(space & game_space);

private:
  std::unique_ptr<shader_program> p_textured_shader_prog;
  std::unique_ptr<shader_program> p_debug_shader_prog;

  // Move elsewhere when game_hack is removed
  debug_draw_manager p_world_ddraw;
  debug_draw_manager p_hud_ddraw;
  // TODO - Move to engine when game_hack is removed
  profiling_records p_profiling_records;
  // TODO - Move to its own space/scene when game_hack is removed
  perf_vis p_perf_vis;

  engine & p_engine;

  bool p_ddraw_enabled = false;
};

} // namespace LE

#endif // LE_GAME_GAME_HACK_H
