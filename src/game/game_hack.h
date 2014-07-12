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

#include <common/unique_id.h>

#include <devui/perf_vis.h>

#include <engine/component_base.h>
#include <engine/space.h>
#include <engine/sprite_component.h>

#include <graphics/shader_program.h>

#include <math/vec.h>
#include <math/mat.h>

namespace LE
{

class game_hack_component : public logic_component_base
{
public:
  explicit game_hack_component(entity & owner);
  virtual void update(float dt);

  static unique_id<logic_component_base> const type_id;

private:
  bool p_input(space * game_space, float dt);
  void p_logic(space * game_space, float dt);
  void p_physics(space * game_space, float dt);

  // TODO - Move to its own space/scene when game_hack_scene is removed
  bool p_ddraw_enabled = false;
};

} // namespace LE

#endif // LE_GAME_GAME_HACK_H
