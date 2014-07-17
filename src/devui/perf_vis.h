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
  struct settings
  {
    /*
     * The bottom left of the first drawn graph in hud space.
     * Default is arbitrary.
     */
    vec2 bottom_left = vec2(-200.0f, -100.0f);

    /*
     * Dimensions of a single graph in hud space.
     * Default is arbitrary.
     */
    vec2 dimensions = vec2(400.0f, 200.0f);

    /*
     * How far apart graphs are from eachother, in terms of percent of graph dimension.
     *   For example: if {0.0, 1.0}, graphics will be displayed directly ontop of eachother -
     *   as they are offset (1.0 * dimensions.y) from eachother
     * Default is zero, all graphs drawn ontop of eachother.
     */
    vec2 offset_percent = vec2::zero;

    /*
     * Controls how the values of the graph are scaled (where a value == max_time would be
     *   at the dotted line at the top of the graph).
     * Default corresponds to frame time for 60 fps.
     */
    float max_time = 0.016f;

    unsigned label_text_size = 12;

    // by default aligned with right edge of text on left edge of graph, this provides offset from that
    int label_text_offset = 4;

    // TODO - Move settings into perf_vis_component and make getters/setters
  };

  perf_vis();
  virtual ~perf_vis() {}

  virtual void update(float dt);

  void set_label_color(std::string const& label, vec4 const& color);
  vec4 get_label_color(std::string const& label) const;

  settings m_settings;

  static unique_id<logic_component_base> const type_id;

private:
  void p_draw_scaffold(
    debug_draw_manager & hud_ddraw,
    vec2 const& bottom_left,
    vec2 const& dimensions,
    vec4 const& color) const;

  void p_draw_graph(
    debug_draw_manager & hud_ddraw,
    std::string const& name,
    profiling_records::time_record const& record,
    size_t max_num_records_entries,
    vec2 const& bottom_left,
    vec2 const& dimensions,
    vec4 const& color);

  entity * p_get_label_text_entity(std::string const& name);

  std::unordered_map<std::string, vec4> p_label_colors;
};

} // namespace LE

#endif // LE_DEVUI_PERF_VIS_H
