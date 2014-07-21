/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "perf_vis.h"

#include <LE/common/cppformat.h>
#include <LE/engine/engine.h>
#include <LE/engine/entity.h>
#include <LE/engine/space.h>
#include <LE/engine/sprite_component.h>
#include <LE/engine/transform_component.h>
#include <LE/engine/TTF_system.h>
#include <LE/graphics/debug_draw_manager.h>

namespace LE
{

/*!
* \brief \see logic_component_base
*/
unique_id<logic_component_base> const perf_vis::type_id;

/*!
 * \brief Runs performance visualization logic. \see perf_vis for details.
 *
 * \param dt - Unused.
 */
void perf_vis::update(float dt)
{
  LE_UNUSED_VAR(dt);

  auto * owning_space = get_owning_entity()->get_owning_space();
  auto & hud_ddraw = owning_space->m_hud_ddraw;
  auto const& records = owning_space->get_owning_engine()->get_profiling_records();

  // Reserve space for all lines upfront
  // - Scaffolding consists of 2 solid lines and 1 dashed line per graph.
  // - Graph consists of (number of entries in a graph) lines per graph.
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
    auto const& name = key_record_pair.first;
    auto const& record = key_record_pair.second;
    auto const& graph_color = get_graph_color(name);

    p_draw_scaffold(
      hud_ddraw,
      curr_bottom_left,
      p_dimensions,
      vec4(1.0f, 1.0f, 1.0f, 1.0f));

    p_draw_graph(
      hud_ddraw,
      record,
      records.get_max_num_record_entries(),
      curr_bottom_left,
      p_dimensions,
      graph_color);

     p_update_graph_label(
      name,
      p_get_graph_entry_height_offset(record.front(), p_dimensions.y()),
      curr_bottom_left,
      graph_color);

    curr_bottom_left += offset_amount;
  }

  // Update indicator for the current max time below the lower left corner of the first graph
  auto * max_time_text_ent = p_get_text_entity(
    "pv_max_time_indicator",
    fmt::format("Max Time: {} seconds", p_max_time),
    p_text_size_is_dirty);
  auto * max_time_text_t = max_time_text_ent->get_component<transform_component>();
  auto * max_time_text_s = max_time_text_ent->get_component<sprite_component>();
  max_time_text_t->set_pos(
    p_bottom_left.x() + (max_time_text_s->get_dimensions().x() / 2.0f),
    p_bottom_left.y() - (max_time_text_s->get_dimensions().y() / 2.0f));

  p_text_size_is_dirty = false;
}

/*!
 * \brief The color of the graph drawn for a \ref profiling_records "profiling_record" entry
 *   named \p name.
 *
 * If a profiling_point named \p name is recorded by this engine's profiling_records, the
 *   graph drawn for it will have color \p color.
 */
void perf_vis::set_graph_color(std::string const& name, vec4 const& color)
{
  p_graph_colors[name] = color;
}

/*!
 * \brief Gets the graph color associated with \p name.
 *
 * \return The color associated with \p name, if none is specified then color white is returned.
 */
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

/*!
 * \brief The bottom left of the first drawn graph in HUD space.
 *
 * \note Default is arbitrary, should be set manually before use.
 */
void perf_vis::set_bottom_left(vec2 const& value)
{
  p_bottom_left = value;
}

/*!
 * \brief Dimensions of a single graph in HUD space.
 *
 * \note Default is arbitrary, should be set manually before use.
 */
void perf_vis::set_dimensions(vec2 const& value)
{
  p_dimensions = value;
}

/*!
 * \brief How far apart graphs are from eachother, in terms of percent of graph \ref
 *  set_dimensions "dimension".
 *
 * For example: if equal to `{0.0, 1.0}`, graphics will be displayed directly ontop of
 *   eachother, as they are offset `(1.0 * dimensions.y)` from eachother.
 *
 * \note Default is zero, all graphs drawn ontop of eachother.
 *
 * \remarks
 * While a negative y offset is possible, a positive offset is preferred as the text
 *   indicator for \ref set_max_time "the maximum time" will be drawn below the first
 *   graph.
 */
void perf_vis::set_offset_percent(vec2 const& value)
{
  p_offset_percent = value;
}

/*!
 * \brief Controls how the values on the graph are scaled to fit the \ref set_dimensions
 *   "dimensions".
 *
 * If a value on the graph is equal to max_time it will appear at the dotted line at the top
 *   of the graph.
 *
 * \note Default is approximate frame time for 60 fps (0.016).
 */
void perf_vis::set_max_time(float value)
{
  p_max_time = value;

  p_get_text_entity(
    "pv_max_time_indicator",
    fmt::format("Max Time: {} seconds", p_max_time),
    true);
}

/*!
 * \brief Font size (height) of all text used by perf_vis in HUD space.
 *
 * \note Default is arbitrary, should be set manually before use.
 */
void perf_vis::set_text_height(unsigned value)
{
  p_text_height = value;
  p_text_size_is_dirty = true;
}

/*!
 * The horizontal offset at which the name of a graph will appear from the left edge of the
 *   graph.
 *
 * \note Default is 0.0, name drawn right aligned to left side of graph.
 */
void perf_vis::set_graph_name_offset(float value)
{
  p_graph_name_offset = value;
}

/*!
 * \brief Draws scaffolding for a graph which consists of lines along the left and bottom
 *   of the graph, and a dashed line along the top of the graph.
 *
 * \param[in,out] hud_ddraw - The debug_draw_manager to draw lines with.
 * \param bottom_left - The bottom left position of the graph.
 * \param dimensions - The dimensions of the graph.
 * \param color - The color to use when drawing all lines.
 */
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

/*!
 * \brief Draws a graph from entries in a \ref profiling_records::time_record "time record".
 *
 * \param hud_ddraw - The debug_draw_manager to draw lines with.
 * \param record - The time record to use to draw the graph.
 * \param max_num_records_entries - Controls the horizontal scaling of the graph. The
 *   (`max_num_record_entries - 1`)'th entry (see \ref perf_vis for why `- 1` is used will be on
 *   the Bright hand edge of the graph.
 * \param bottom_left - The bottom left position of the graph.
 * \param dimensions - The dimensions of the graph.
 * \param color - The color to use when drawing all lines.
 */
void perf_vis::p_draw_graph(
  debug_draw_manager & hud_ddraw,
  profiling_records::time_record const& record,
  size_t max_num_records_entries,
  vec2 const& bottom_left,
  vec2 const& dimensions,
  vec4 const& color) const
{
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
    vec2 curr_point(
      curr_x,
      bottom_left.y() + p_get_graph_entry_height_offset(*record_entry_it, dimensions.y()) );

    hud_ddraw.lines.add_line(prev_point, curr_point, color);

    curr_x += delta_x;

    prev_point = curr_point;
  }
}

/*!
 * \brief Updates the position of a graph label so that it is aligned to right side of the graph
 *   horizontally and to the drawn height of the oldest drawn graph vertically.
 *
 * \param name - The name of graph, also the text that will be displayed.
 * \param height_offset - Offset from bottom_left.y() that the text will be vertically centered
 *   at.
 * \param bottom_left - The bottom left of the graph.
 * \param color - Color the text should be displayed in.
 */
void perf_vis::p_update_graph_label(
    std::string const& name,
    float height_offset,
    vec2 const& bottom_left,
    vec4 const& color)
{
  auto * name_text_ent = p_get_text_entity(name, name, p_text_size_is_dirty);
  auto * name_text_t = name_text_ent->get_component<transform_component>();
  auto * name_text_s = name_text_ent->get_component<sprite_component>();
  name_text_t->set_pos(
    bottom_left.x() - (name_text_s->get_dimensions().x() / 2.0f) - p_graph_name_offset,
    bottom_left.y() + height_offset );
  name_text_s->m_color = color;
}

/*!
 * \brief Gets an entity used for displaying text. If one does not exist already one will be
 *   created.
 *
 * \param name - The name associated with this text.
 * \param text - The text to render
 * \param update_text_if_preexisting - Forces text to be re-rendered if an entity already
 *   exists. Otherwise text will only be rendered upon creation of the entity.
 *
 * \return A pointer to the entity to be used for \p name.
 */
entity * perf_vis::p_get_text_entity(
    std::string const& name,
    std::string const& text,
    bool update_text_if_preexisting)
{
  // Prepend arbitrary prefix to the perf_vis owned entities.
  std::string const ent_name = "pv_" + name;

  // Check if we've already created an entity for this text.
  auto * result = get_owning_entity()->find_child(ent_name);
  if(result == nullptr)
  {
    // An entity for this graph's text does not yet exist, create it and set it up for text
    //   drawing.
    result = get_owning_entity()->get_owning_space()->create_entity(ent_name);

    result->create_component<sprite_component>(
      TTF_system::render_text_to_texture(text, p_text_height));

    get_owning_entity()->add_child(result);
  }
  else
  {
    if(update_text_if_preexisting)
    {
      // Re-render text
      auto * text_s = result->get_component<sprite_component>();
      LE_FATAL_ERROR_IF(text_s == nullptr, "Missing sprite component!");
      text_s->set_texture(
        TTF_system::render_text_to_texture(text, p_text_height));
    }
  }

  return result;
}

/*!
 * \brief Gets the height offset from the bottom of a graph at which an entry should be
 *   displayed.
 *
 * \param entry_value - The value of the entry.
 * \param graph_height - The height of the graph.
 *
 * \return The height offset.
 */
float perf_vis::p_get_graph_entry_height_offset(float entry_value, float graph_height) const
{
  return (entry_value / p_max_time) * graph_height;
}

} // namespace LE
