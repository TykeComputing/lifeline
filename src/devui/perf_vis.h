/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_DEVUI_PERF_VIS_H
#define LE_DEVUI_PERF_VIS_H

#include <string>
#include <unordered_map>

#include <common/profiling_records.h>
#include <common/unique_id.h>

#include <engine/logic_component_base.h>

#include <math/vec.h>

namespace LE
{

class debug_draw_manager;

class perf_vis : public logic_component_base
{
public:
  perf_vis(entity & owner);
  virtual ~perf_vis() {}

  virtual void update(float dt);

  void draw(debug_draw_manager & hud_ddraw, profiling_records const& records) const;

  void draw_scaffold(
    debug_draw_manager & hud_ddraw,
    vec2 const& bottom_left,
    vec2 const& dimensions,
    vec4 const& color) const;

  void draw_graph(
    debug_draw_manager & hud_ddraw,
    std::string const& name,
    profiling_records::time_record const& record,
    size_t max_num_records_entries,
    vec2 const& bottom_left,
    vec2 const& dimensions,
    vec4 const& color) const;

  void set_label_color(std::string const& label, vec4 const& color);
  vec4 get_label_color(std::string const& label) const;

  static unique_id<logic_component_base> const type_id;

private:
  std::unordered_map<std::string, vec4> p_label_colors;
};

} // namespace LE

#endif // LE_DEVUI_PERF_VIS_H
