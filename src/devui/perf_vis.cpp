/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "perf_vis.h"

#include <graphics/debug_draw_manager.h>

#include <engine/engine.h>
#include <engine/entity.h>
#include <engine/space.h>

namespace LE
{

unique_id<logic_component_base> const perf_vis::type_id;

perf_vis::perf_vis(entity & owner) :
  logic_component_base(owner)
{
  // TODO - Move to devui setup component?
  set_label_color("update", vec4(0.0f, 0.0f, 1.0f, 1.0f));
  set_label_color("graphics_system", vec4(1.0f, 0.0f, 0.0f, 1.0f));
  set_label_color("buffer_swap", vec4(1.0f, 1.0f, 0.0f, 1.0f));
  set_label_color("total_frame", vec4(0.0f, 1.0f, 0.0f, 1.0f));
}

void perf_vis::update(float dt)
{
  LE_UNUSED_VAR(dt);

  auto * owning_space = get_owning_entity()->get_owning_space();
  auto const& owning_engine = owning_space->get_owning_engine();
  draw(owning_space->m_hud_ddraw, owning_engine->get_profiling_records());
}

void perf_vis::draw(debug_draw_manager & hud_ddraw, profiling_records const& records) const
{
  // Reserve space for all lines upfront
  size_t const num_scaffold_lines = records.get_num_records() * 2;
  size_t const num_graph_lines = records.get_num_records() * records.get_num_record_entries();

  size_t const num_scaffold_dashed_lines = records.get_num_records() * 1;

  hud_ddraw.lines.reserve_lines(num_scaffold_lines + num_graph_lines);
  hud_ddraw.dashed_lines.reserve_lines(num_scaffold_dashed_lines);

  // Draw a graph for each label
  vec2 const offset_amount = m_settings.dimensions * m_settings.offset_percent;
  vec2 curr_bottom_left = m_settings.bottom_left;

  for(auto const& key_record_pair : records)
  {
    draw_scaffold(
      hud_ddraw,
      curr_bottom_left,
      m_settings.dimensions,
      vec4(1.0f, 1.0f, 1.0f, 1.0f));

    draw_graph(
      hud_ddraw,
      key_record_pair.first,
      key_record_pair.second,
      records.get_max_num_record_entries(),
      curr_bottom_left,
      m_settings.dimensions,
      get_label_color(key_record_pair.first));

    curr_bottom_left += offset_amount;
  }
}

void perf_vis::draw_scaffold(
  debug_draw_manager & hud_ddraw,
  vec2 const& bottom_left,
  vec2 const& dimensions,
  vec4 const& color) const
{
  vec2 const bottom_right(bottom_left.x() + dimensions.x(), bottom_left.y());
  vec2 const top_left(bottom_left.x(), bottom_left.y() + dimensions.y());
  vec2 const top_right(bottom_left + dimensions);

  hud_ddraw.lines.add_line(bottom_left, bottom_right, color);
  hud_ddraw.lines.add_line(bottom_left, top_left, color);
  hud_ddraw.dashed_lines.add_line(top_left, top_right, color * 0.5f);
}

void perf_vis::draw_graph(
  debug_draw_manager & hud_ddraw,
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

    hud_ddraw.lines.add_line(prev_point, curr_point, color);

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
