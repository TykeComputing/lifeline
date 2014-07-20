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

/*!
 * \brief Draws performance visualization graphs to the HUD.
 *
 * Uses results stored in owning \ref engine "engine's" profiling_records to draw performance
 *   visualization graphs (using the owning space's HUD debug_draw_manager). Will create new
 *   child \ref entity "entities" to display text.
 *
 */
class perf_vis : public logic_component_base
{
public:
  perf_vis();

  /*!
   * \brief Runs performance visualization logic. \see perf_vis for details.
   *
   * \param dt - Unused.
   */
  virtual void update(float dt);

  /*!
   * \brief The color of the graph drawn for a \ref profiling_records "profiling_record" entry
   *   named \p name.
   *
   * If a profiling_point named \p name is recorded by this engine's profiling_records, the
   *   graph drawn for it will have color \p color.
   *
   * \note If no color is provided for a name the color white is used.
   */
  void set_graph_color(std::string const& name, vec4 const& color);
  vec4 const& get_graph_color(std::string const& name) const;

  /*!
   * \brief The bottom left of the first drawn graph in HUD space.
   *
   * \note Default is arbitrary.
   */
  void set_bottom_left(vec2 const& value) { p_bottom_left = value; }
  vec2 const& get_bottom_left() const { return p_bottom_left; }

  /*!
   * \brief Dimensions of a single graph in HUD space.
   *
   * \note Default is arbitrary.
   */
  void set_dimensions(vec2 const& value) { p_dimensions = value; }
  vec2 const& get_dimensions() const { return p_dimensions; }

  /*!
   * \brief How far apart graphs are from eachother, in terms of percent of graph dimension.
   *
   * For example: if {0.0, 1.0}, graphics will be displayed directly ontop of eachother - as
   *   they are offset (1.0 * dimensions.y) from eachother.
   *
   * \note Default is zero, all graphs drawn ontop of eachother.
   *
   * \remarks
   * While a negative y offset is possible, a positive offset is preferred as the text
   *   indicator for \ref set_max_time "the maximum time" will be drawn below the first
   *   graph.
   */
  void set_offset_percent(vec2 const& value) { p_offset_percent = value; }
  vec2 const& get_offset_percent() const { return p_offset_percent; }

  /*!
   * \brief Controls how the values on the graph are scaled to fit the dimensions (\see
   *   set_dimensions).
   *
   * If a value on the graph is equal to max_time it will appear at the dotted line at the top
   *   of the graph).
   *
   * \note Default is approximate frame time for 60 fps (0.016).
   */
  void set_max_time(float value);
  float get_max_time() const { return p_max_time; }

  /*!
   * \brief Size of all text used by this.
   *
   * \note Default is arbitrary.
   */
  void set_text_point_size(unsigned value);
  unsigned get_text_point_size() const { return p_text_point_size; }

  /*!
   * The horizontal offset at which the name of a graph will appear from the left edge of the
   *   graph.
   *
   * \note Default is 0.0, name drawn right aligned to left side of graph.
   */
  void set_graph_name_offset(float value) { p_graph_name_offset = value; }
  float get_graph_name_offset() const { return p_graph_name_offset; }

  /*!
   * \brief \see logic_component_base
   */
  static unique_id<logic_component_base> const type_id;

private:
  void p_draw_scaffold(
    debug_draw_manager & hud_ddraw,
    vec2 const& p_bottom_left,
    vec2 const& p_dimensions,
    vec4 const& color) const;

  void p_draw_graph(
    debug_draw_manager & hud_ddraw,
    std::string const& name,
    profiling_records::time_record const& record,
    size_t max_num_records_entries,
    vec2 const& p_bottom_left,
    vec2 const& p_dimensions,
    vec4 const& color); // TODO - const?

  entity * p_get_text_entity(
    std::string const& name,
    std::string const& text,
    bool update_text_if_exists);

  std::unordered_map<std::string, vec4> p_graph_colors;

  // Settings
  vec2 p_bottom_left = vec2(-200.f, -100.f);
  vec2 p_dimensions = vec2(400.f, 200.f);
  vec2 p_offset_percent = vec2::zero;
  float p_max_time = 0.016f;
  unsigned p_text_point_size = 12;
  float p_graph_name_offset = 0.f;

  // Signals that text will need to be re-rendered
  bool p_text_size_is_dirty = false;
};

} // namespace LE

#endif // LE_DEVUI_PERF_VIS_H
