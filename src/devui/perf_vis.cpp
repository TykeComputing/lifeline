/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "perf_vis.h"

#include <common/cppformat.h>

#include <engine/engine.h>
#include <engine/entity.h>
#include <engine/space.h>
#include <engine/sprite_component.h>
#include <engine/transform_component.h>
#include <engine/TTF_system.h>

#include <graphics/debug_draw_manager.h>

namespace LE
{

unique_id<logic_component_base> const perf_vis::type_id;

perf_vis::perf_vis()
{
  // TODO - Move to devui setup component?
  set_graph_color("update", vec4(0.0f, 0.0f, 1.0f, 1.0f));
  set_graph_color("graphics_system", vec4(1.0f, 0.0f, 0.0f, 1.0f));
  set_graph_color("buffer_swap", vec4(1.0f, 1.0f, 0.0f, 1.0f));
  set_graph_color("total_frame", vec4(0.0f, 1.0f, 0.0f, 1.0f));
}

void perf_vis::update(float dt)
{
  LE_UNUSED_VAR(dt);

  auto * owning_space = get_owning_entity()->get_owning_space();
  auto & hud_ddraw = owning_space->m_hud_ddraw;
  auto const& records = owning_space->get_owning_engine()->get_profiling_records();

  // Reserve space for all lines upfront
  size_t const num_scaffold_lines = records.get_num_records() * 2;
  size_t const num_graph_lines = records.get_num_records() * records.get_num_record_entries();

  size_t const num_scaffold_dashed_lines = records.get_num_records() * 1;

  hud_ddraw.lines.reserve_lines(num_scaffold_lines + num_graph_lines);
  hud_ddraw.dashed_lines.reserve_lines(num_scaffold_dashed_lines);

  // Draw all graphs
  vec2 const offset_amount = p_dimensions * p_offset_percent;
  vec2 curr_bottom_left = p_bottom_left;

  for(auto const& key_record_pair : records)
  {
    p_draw_scaffold(
      hud_ddraw,
      curr_bottom_left,
      p_dimensions,
      vec4(1.0f, 1.0f, 1.0f, 1.0f));

    p_draw_graph(
      hud_ddraw,
      key_record_pair.first,
      key_record_pair.second,
      records.get_max_num_record_entries(),
      curr_bottom_left,
      p_dimensions,
      get_graph_color(key_record_pair.first));

    curr_bottom_left += offset_amount;
  }

  // Draw an indicator for the current max time below the lower left corner of the first graph
  auto * max_time_text_ent = p_get_text_entity(
    "pv_max_time_indicator",
    fmt::format("Max Time: {}", p_max_time),
    p_text_size_is_dirty);
  auto * max_time_text_t = max_time_text_ent->get_component<transform_component>();
  auto * max_time_text_s = max_time_text_ent->get_component<sprite_component>();
  max_time_text_t->set_pos(
    p_bottom_left.x() + (max_time_text_s->get_dimensions().x() / 2.0f),
    p_bottom_left.y() - (max_time_text_s->get_dimensions().y() / 2.0f));

  p_text_size_is_dirty = false;
}

void perf_vis::set_graph_color(std::string const& name, vec4 const& color)
{
  p_graph_colors[name] = color;
}

vec4 const& perf_vis::get_graph_color(std::string const& name) const
{
  auto find_it = p_graph_colors.find(name);
  if(find_it != p_graph_colors.end())
  {
    return find_it->second;
  }
  else
  {
    static vec4 const default_color(1.0f, 1.0f, 1.0f, 1.0f);
    return default_color;
  }
}

void perf_vis::set_max_time(float value)
{
  p_max_time = value;

  p_get_text_entity(
    "pv_max_time_indicator",
    fmt::format("Max Time: {}", p_max_time),
    true);
}

void perf_vis::set_text_point_size(unsigned value)
{
  p_text_point_size = value;
  p_text_size_is_dirty = true;
}

void perf_vis::p_draw_scaffold(
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

void perf_vis::p_draw_graph(
  debug_draw_manager & hud_ddraw,
  std::string const& name,
  profiling_records::time_record const& record,
  size_t max_num_records_entries,
  vec2 const& bottom_left,
  vec2 const& dimensions,
  vec4 const& color)
{
  LE_UNUSED_VAR(name);

  if(record.empty())
    return;

  // We will always ignore the most recent entry since that will be the frame currently in
  //   progress. Thus our graph will have max_num_records_entries - 1 plotted points.
  float const delta_x = dimensions.x() / (max_num_records_entries - 1);

  vec2 prev_point = bottom_left;
  prev_point.y() += (record.front() / p_max_time) * dimensions.y();

  float curr_x = bottom_left.x() + delta_x;

  // Draw records, ignoring most recent record (since this frame is not finished)
  for(auto record_entry_it = record.cbegin();
      record_entry_it != (record.cend() - 1);
      ++record_entry_it)
  {
    vec2 curr_point(curr_x, bottom_left.y());
    curr_point.y() += (*record_entry_it / p_max_time) * dimensions.y();

    hud_ddraw.lines.add_line(prev_point, curr_point, color);

    curr_x += delta_x;

    prev_point = curr_point;
  }

  // Draw graph's name
  auto * name_text_ent = p_get_text_entity(name, name, p_text_size_is_dirty);
  auto * name_text_t = name_text_ent->get_component<transform_component>();
  auto * name_text_s = name_text_ent->get_component<sprite_component>();
  name_text_t->set_pos(
    bottom_left.x() - (name_text_s->get_dimensions().x() / 2.0f) - p_graph_name_offset,
    bottom_left.y() + ((record.front() /p_max_time) * dimensions.y()) );
  name_text_s->m_color = color;
}

entity * perf_vis::p_get_text_entity(
    std::string const& name,
    std::string const& text,
    bool update_text_if_preexisting)
{
  std::string const ent_name = "pv_" + name;

  auto * result = get_owning_entity()->find_child(ent_name);
  if(result == nullptr)
  {
    // An entity for this graph's text does not yet exist, create it.
    result = get_owning_entity()->get_owning_space()->create_entity(ent_name);

    result->create_component<sprite_component>(
      TTF_system::render_text_to_texture(text, p_text_point_size));

    get_owning_entity()->add_child(result);
  }
  else
  {
    if(update_text_if_preexisting)
    {
      auto * text_s = result->get_component<sprite_component>();
      LE_FATAL_ERROR_IF(text_s == nullptr, "Missing sprite component!");
      text_s->set_texture(
        TTF_system::render_text_to_texture(text, p_text_point_size));
    }
  }

  return result;
}

} // namespace LE
