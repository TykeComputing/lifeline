/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "camera_component.h"

#include <LE/engine/entity.h>
#include <LE/engine/engine.h>
#include <LE/engine/space.h>
#include <LE/engine/transform_component.h>

namespace LE
{

unique_id<engine_component_base> const camera_component::type_id;

camera_component::camera_component(uvec2 const& dim, uvec2 const& viewport_pos, uvec2 const& viewport_dim)
: p_dim(dim)
, p_viewport_pos(viewport_pos)
, p_viewport_dim(viewport_dim)
{
  LE_FATAL_ERROR_IF(p_dim.x() <= 0u || p_dim.y() <= 0u, "Invalid dimensions!");

  vec2 const half_dim = vec2(p_dim) * 0.5f;
  p_cam_to_proj = mat3mk(
    (1.0f / half_dim.x()),                  0.0f, 0.0f,
                     0.0f, (1.0f / half_dim.y()), 0.0f,
                     0.0f,                  0.0f, 0.0f
  );
}

mat3 camera_component::get_world_to_cam() const
{
  mat3 const& cam_to_world = get_owning_entity()->get_component<transform_component>()->get_matrix();
  return get_inverse(cam_to_world);
}

mat3 const& camera_component::get_cam_to_proj() const
{
  return p_cam_to_proj;
}

uvec2 const& camera_component::get_dim() const
{
  return p_dim;
}

uvec2 const& camera_component::get_viewport_pos() const
{
  return p_viewport_pos;
}

uvec2 const& camera_component::get_viewport_dim() const
{
  return p_viewport_dim;
}

vec2 camera_component::viewport_to_world_space(uvec2 const& viewport_pos) const
{
  engine const* eng = get_owning_entity()->get_owning_space()->get_owning_engine();
  uvec2 actual_window_size = eng->get_window().get_size();
  uvec2 render_target_size = eng->get_graphics_system().get_render_target_size();
  uvec2 actual_to_render_ratios = actual_window_size / render_target_size;

  vec2 result = vec2(viewport_pos);
  result = result / vec2(actual_to_render_ratios);
  result -= (vec2(render_target_size) * 0.5f); // Move origin to center
  result.y() = -result.y();

  result = vec2(get_owning_entity()->get_component<transform_component>()->get_matrix() * vec3(vec2(result), 1.0f));
  return result;
}

} // namespace LE
