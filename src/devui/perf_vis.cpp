/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "perf_vis.h"

#include <graphics/debug_drawer.h>

namespace LE
{

perf_vis::perf_vis()
{

}

void perf_vis::draw(debug_line_drawer & hud_drawer, profiling_records const& records) const
{
  LE_UNUSED_VAR(hud_drawer);

  vec2 const bottom_left(-0.9f, -0.9f);
  vec2 const dimensions(1.8f, 1.8f);
  vec4 const color(1.0f, 1.0f, 1.0f, 1.0f);

  size_t num_scaffold_lines = 1 * 3;
  size_t num_graph_lines = records.get_num_records() * records.get_num_record_entries();

  hud_drawer.reserve_lines(num_scaffold_lines + num_graph_lines);

  draw_scaffold(hud_drawer, bottom_left, dimensions, color);

  for(auto const& key_record_pair : records)
  {
    draw_graph(
      hud_drawer,
      key_record_pair.first,
      key_record_pair.second,
      records.get_max_num_record_entries(),
      bottom_left,
      dimensions,
      get_label_color(key_record_pair.first));
  }
}

void perf_vis::draw_scaffold(
  debug_line_drawer & hud_drawer,
  vec2 const& bottom_left,
  vec2 const& dimensions,
  vec4 const& color) const
{
  vec2 const bottom_right(bottom_left.x() + dimensions.y(), bottom_left.y());
  vec2 const top_left(bottom_left.x(), bottom_left.y() + dimensions.y());
  vec2 const top_right(bottom_left + dimensions);

  hud_drawer.add_line(bottom_left, bottom_right, color);
  hud_drawer.add_line(bottom_left, top_left, color);
  //hud_drawer.add_line(top_left, top_right, color * 0.5f);
}

void perf_vis::draw_graph(
  debug_line_drawer & hud_drawer,
  std::string const& name,
  profiling_records::time_record const& record,
  size_t max_num_records_entries,
  vec2 const& bottom_left,
  vec2 const& dimensions,
  vec4 const& color) const
{
  LE_UNUSED_VAR(name);
  if(record.empty())
    return;

  // We will always ignore the most recent entry, thus our graph will have
  //   max_num_records_entries - 1 plotted points.
  float const delta_x = dimensions.x() / (max_num_records_entries - 1);
  float const target_val = 0.016f;

  vec2 prev_point = bottom_left;
  prev_point.y() += (record.front() / target_val) * dimensions.y();

  float curr_x = bottom_left.x() + delta_x;

  // Draw records, ignoring most recent record (since this frame is not finished)
  for(auto record_entry_it = record.cbegin();
      record_entry_it != (record.cend() - 1);
      ++record_entry_it)
  {
    vec2 curr_point(curr_x, bottom_left.y());
    curr_point.y() += (*record_entry_it / target_val) * dimensions.y();

    hud_drawer.add_line(prev_point, curr_point, color);

    curr_x += delta_x;

    prev_point = curr_point;
  }
}

void perf_vis::set_label_color(std::string const& label, vec4 const& color)
{
  p_label_colors[label] = color;
}

vec4 perf_vis::get_label_color(std::string const& label) const
{
  auto find_it = p_label_colors.find(label);
  if(find_it != p_label_colors.end())
  {
    return find_it->second;
  }
  else
  {
    return vec4(1.0f, 1.0f, 1.0f, 1.0f);
  }
}

} // namespace LE
