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

#include <LE/common/unique_id.h>
#include <LE/devui/perf_vis.h>
#include <LE/engine/component_base.h>
#include <LE/engine/space.h>
#include <LE/graphics/shader_program.h>
#include <LE/math/vec.h>
#include <LE/math/mat.h>

namespace LE
{

class game_hack : public logic_component_base
{
public:
  virtual void initialize();
  virtual void update(float dt);

  static unique_id<logic_component_base> const type_id;

private:
  void p_input();
  void p_display_controls_logic();
  void p_physics(float dt);

  space * p_get_perf_vis_space();
  perf_vis * p_get_perf_vis_component();

  void p_set_perf_vis_overlapped(perf_vis * pv) const;
  void p_set_perf_vis_vertical(perf_vis * pv) const;
};

} // namespace LE

#endif // LE_GAME_GAME_HACK_H
