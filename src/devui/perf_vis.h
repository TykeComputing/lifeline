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
 * Uses results stored in the owning engine's profiling_records to draw performance
 *   visualization graphs (using the owning space's HUD debug_draw_manager). Will create new
 *   child entites (\ref entity) to display text labels for each graph.
 */
class perf_vis : public logic_component_base
{
public:
  perf_vis();

  /*!
   * \brief Runs performance visualization logic.
   *
   *  - Draws lines for graphs to the owning space's HUD debug drawer.
   *  - Uses profiling records from owning engine, ignoring the current frame's records.
   *  - Adds sprites to
   */
  virtual void update(float dt);

  /*!
   * \brief The color of the graph drawn for a record named \p label.
   *
   * If a profiling_point records named \p label is recorded in the processed profiling_records,
   *   the graph drawn for it will have color \p color.
   */
  void set_label_color(std::string const& label, vec4 const& color);
  vec4 get_label_color(std::string const& label) const;

  /*!
   * \brief The bottom left of the first drawn graph in HUD space.
   *
   * Default is arbitrary.
   */
  void set_bottom_left(vec2 const& value) { p_bottom_left = value; }
  vec2 const& get_bottom_left() const { return p_bottom_left; }

  /*!
   * \brief Dimensions of a single graph in HUD space.
   *
   * Default is arbitrary.
   */
  void set_dimensions(vec2 const& value) { p_dimensions = value; }
  vec2 const& get_dimensions() const { return p_dimensions; }

  /*!
   * \brief How far apart graphs are from eachother, in terms of percent of graph dimension.
   *
   * For example: if {0.0, 1.0}, graphics will be displayed directly ontop of eachother - as
   *   they are offset (1.0 * dimensions.y) from eachother.
   * Default is zero, all graphs drawn ontop of eachother.
   */
  void set_offset_percent(vec2 const& value) { p_offset_percent = value; }
  vec2 const& get_offset_percent() const { return p_offset_percent; }

  /*!
   * \brief Controls how the values on the graph are scaled to fit the dimensions.
   *
   * If a value on the graph is equal to max_time it will appear at the dotted line at the top
   *   of the graph).
   * Default is approximate frame time for 60 fps (0.016).
   */
  void set_max_time(float value);
  float get_max_time() const { return p_max_time; }

  /*!
   * \brief Size of text used to label each graph in HUD space.
   */
  void set_text_point_size(unsigned value);

  /*!
   * \brief \ref set_text_point_size()
   */
  unsigned get_text_point_size() const { return p_text_point_size; }

  // by default aligned with right edge of text on left edge of graph, this provides offset from that
  // + will move further to left
  void set_label_text_offset(int value) { p_label_text_offset = value; }
  int get_label_text_offset() const { return p_label_text_offset; }

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

  std::unordered_map<std::string, vec4> p_label_colors;

  // Settings
  vec2 p_bottom_left = vec2(-200.f, -100.f);
  vec2 p_dimensions = vec2(400.f, 200.f);
  vec2 p_offset_percent = vec2::zero;
  float p_max_time = 0.016f;
  unsigned p_text_point_size = 12;
  int p_label_text_offset = 4;

  // Signals that text will need to be re-rendered
  bool p_text_size_is_dirty = false;
};

} // namespace LE

#endif // LE_DEVUI_PERF_VIS_H
