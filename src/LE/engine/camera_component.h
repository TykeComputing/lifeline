/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_CAMERA_COMPONENT_H
#define LE_ENGINE_CAMERA_COMPONENT_H

#include <LE/common/unique_id.h>

#include <LE/engine/engine_component_base.h>

#include <LE/math/mat.h>
#include <LE/math/vec.h>

namespace LE
{

// 2D orthographic camera
class camera_component : public engine_component_base
{
public:
  camera_component(uvec2 const& dim, uvec2 const& viewport_pos, uvec2 const& viewport_dim);
  virtual ~camera_component() {}
  
  static unique_id<engine_component_base> const type_id;

  mat3 get_world_to_cam() const;
  mat3 const& get_cam_to_proj() const;

  uvec2 const& get_dim() const;
  uvec2 const& get_viewport_pos() const;
  uvec2 const& get_viewport_dim() const;

  vec2 viewport_to_world_space(uvec2 const& viewport_pos) const;

private:
  mat3 p_cam_to_proj;
  uvec2 p_dim;
  uvec2 p_viewport_pos;
  uvec2 p_viewport_dim;
};

} // namespace LE

#endif // LE_ENGINE_CAMERA_COMPONENT_H
