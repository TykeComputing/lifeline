/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_DEVUI_PERF_VIS_H
#define LE_DEVUI_PERF_VIS_H

#include <string>
#include <unordered_map>

#include <LE/common/profiling_records.h>
#include <LE/common/unique_id.h>
#include <LE/engine/logic_component_base.h>
#include <LE/math/vec.h>

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
 * \note The most recent entry in the profiling_records will be ignored, as it will be assumed
 *   to be for the frame currently in progress.
 */
class perf_vis : public logic_component_base
{
public:
  virtual void update(float dt);

  void set_graph_color(std::string const& name, vec4 const& color);
  vec4 const& get_graph_color(std::string const& name) const;

  void set_bottom_left(vec2 const& value);
  vec2 const& get_bottom_left() const { return p_bottom_left; }

  void set_dimensions(vec2 const& value);
  vec2 const& get_dimensions() const { return p_dimensions; }

  void set_offset_percent(vec2 const& value);
  vec2 const& get_offset_percent() const { return p_offset_percent; }

  void set_max_time(float value);
  float get_max_time() const { return p_max_time; }

  void set_text_height(unsigned value);
  unsigned get_text_height() const { return p_text_height; }

  void set_graph_name_offset(float value);
  float get_graph_name_offset() const { return p_graph_name_offset; }

  static unique_id<logic_component_base> const type_id;

private:
  void p_draw_scaffold(
    debug_draw_manager & hud_ddraw,
    vec2 const& bottom_left,
    vec2 const& dimensions,
    vec4 const& color) const;

  void p_draw_graph(
    debug_draw_manager & hud_ddraw,
    profiling_records::time_record const& record,
    size_t max_num_records_entries,
    vec2 const& bottom_left,
    vec2 const& dimensions,
    vec4 const& color) const;

  void p_update_graph_label(
    std::string const& name,
    float height,
    vec2 const& bottom_left,
    vec4 const& color);

  entity * p_get_text_entity(
    std::string const& name,
    std::string const& text,
    bool update_text_if_exists);

  float p_get_graph_entry_height_offset(float entry_value, float graph_height) const;

  std::unordered_map<std::string, vec4> p_graph_colors; //! see \ref set_graph_color

  vec2 p_bottom_left = vec2::zero;    //!< see \ref set_bottom_left
  vec2 p_dimensions = vec2::zero;     //!< see \ref set_dimensions
  vec2 p_offset_percent = vec2::zero; //!< see \ref set_offset_percent
  float p_max_time = 0.016f;          //!< see \ref set_max_time
  unsigned p_text_height = 0;         //!< see \ref set_text_height
  float p_graph_name_offset = 0.f;    //!< see \ref set_graph_name_offset
  bool p_text_size_is_dirty = false;  //!< Signals that text will need to be re-rendered
};

} // namespace LE

#endif // LE_DEVUI_PERF_VIS_H
