/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_DEVUI_PERF_VIS_H
#define LE_DEVUI_PERF_VIS_H

#include <string>

#include <common/profiling_records.h>

#include <math/vec.h>

namespace LE
{

class debug_line_drawer;

class perf_vis
{
public:
  perf_vis();

  void draw(debug_line_drawer & hud_drawer, profiling_records const& records) const;

  void draw_scaffold(
    debug_line_drawer & hud_drawer,
    vec2 const& bottom_left,
    vec2 const& dimensions,
    vec4 const& color) const;

  void draw_graph(
    debug_line_drawer & hud_drawer,
    std::string const& name,
    profiling_records::time_record const& record,
    size_t max_num_records_entries,
    vec2 const& bottom_left,
    vec2 const& dimensions,
    vec4 const& color) const;

private:
};

} // namespace LE

#endif // LE_DEVUI_PERF_VIS_H
