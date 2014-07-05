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

#include <math/vec.h>

namespace LE
{

class debug_draw_manager;

class perf_vis
{
public:
  perf_vis();

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

private:
  std::unordered_map<std::string, vec4> p_label_colors;
};

} // namespace LE

#endif // LE_DEVUI_PERF_VIS_H
