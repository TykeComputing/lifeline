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

/*
 * Uses results stored in owning engine's profiling_records to draw performance visualization
 *   graphs. Will create new entites to display text labels for each graph, ideally should be
 *   placed in its own space (if not, be aware that perf_vis will assume all entities named
 *   "pv_*" belong to it).
 */
 // TODO - Make text entities children
class perf_vis : public logic_component_base
{
public:
  perf_vis();
  virtual ~perf_vis() {}

  /*
   * Runs perf_vis logic:
   *   - Draws lines for graphs to the owning space's hud debug drawer.
   *   - Uses profiling records from owning engine, ignoring the current frame's records.
   *   - Adds sprites to
   */
  virtual void update(float dt);

  // TODO - Comment
  void set_label_color(std::string const& label, vec4 const& color);
  vec4 get_label_color(std::string const& label) const;

  /*
   * The bottom left of the first drawn graph in hud space.
   * Default is arbitrary.
   */
  vec2 const& get_bottom_left() const { return p_bottom_left; }
  void set_bottom_left(vec2 const& value) { p_bottom_left = value; }

  /*
   * Dimensions of a single graph in hud space.
   * Default is arbitrary.
   */
  vec2 const& get_dimensions() const { return p_dimensions; }
  void set_dimensions(vec2 const& value) { p_dimensions = value; }

  /*
   * How far apart graphs are from eachother, in terms of percent of graph dimension.
   *   For example: if {0.0, 1.0}, graphics will be displayed directly ontop of eachother -
   *   as they are offset (1.0 * dimensions.y) from eachother
   * Default is zero, all graphs drawn ontop of eachother.
   */
  vec2 const& get_offset_percent() const { return p_offset_percent; }
  void set_offset_percent(vec2 const& value) { p_offset_percent = value; }

  /*
   * Controls how the values of the graph are scaled (where a value == max_time would be
   *   at the dotted line at the top of the graph).
   * Default is approximate frame time for 60 fps (0.016).
   */
  float get_max_time() const { return p_max_time; }
  void set_max_time(float value);

  // TODO - Comment
  unsigned get_text_point_size() const { return p_text_point_size; }
  void set_text_point_size(unsigned value);

  // by default aligned with right edge of text on left edge of graph, this provides offset from that
  // + will move further to left
  int get_label_text_offset() const { return p_label_text_offset; }
  void set_label_text_offset(int value) { p_label_text_offset = value; }

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

  void p_update_max_time_entity_text();

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
