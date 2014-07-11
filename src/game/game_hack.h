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

#include <graphics/shader_program.h>

#include <math/vec.h>
#include <math/mat.h>

namespace LE
{

class space;

class game_hack_scene
{
public:
  explicit game_hack_scene(space * game_space);
  ~game_hack_scene();

  bool input(space & game_space, float dt);
  void logic(space & game_space, float dt);
  void physics(space & game_space, float dt);
  bool update(space & game_space, float dt);

private:
  // TODO - Move to its own space/scene when game_hack_scene is removed
  perf_vis p_perf_vis;

  space * p_owner;

  bool p_ddraw_enabled = false;
};

} // namespace LE

#endif // LE_GAME_GAME_HACK_H
