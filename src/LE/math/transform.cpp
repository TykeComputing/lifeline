/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "transform.h"

#include <LE/math/float.h>

namespace LE
{

/**********************************************/
/* Position */
/**********************************************/
void transform::set_pos(float x, float y)
{
  p_pos.set(x, y);
  mark_as_dirty();
}

void transform::set_pos(vec2 const& value)
{
  set_pos(value[0], value[1]);
}

void transform::set_pos_x(float value)
{
  mark_as_dirty();
  p_pos[0] = value;
}

void transform::set_pos_y(float value)
{
  mark_as_dirty();
  p_pos[1] = value;
}

void transform::set_z_order(float value)
{
  mark_as_dirty();
  p_z_order = value;
}

vec2 const& transform::translate(float x, float y)
{
  return translate(vec2(x, y));
}

vec2 const& transform::translate(vec2 const& value)
{
  mark_as_dirty();
  return p_pos += value;
}

/**********************************************/
/* Scale */
/**********************************************/

void transform::set_scale(float val)
{
  set_scale(val, val);
}

void transform::set_scale(float x, float y)
{
  mark_as_dirty();
  p_scale.set(x, y);
}

void transform::set_scale(vec2 const& value)
{
  set_scale(value[0], value[1]);
}

void transform::set_scale_x(float value)
{
  mark_as_dirty();
  p_scale[0] = value;
}

void transform::set_scale_y(float value)
{
  mark_as_dirty();
  p_scale[1] = value;
}

vec2 const& transform::scale_by(float value)
{
  return scale_by(value, value);
}

vec2 const& transform::scale_by(float x, float y)
{
  return scale_by(vec2(x, y));
}

vec2 const& transform::scale_by(vec2 const& value)
{
  mark_as_dirty();
  return p_pos *= value;
}

/**********************************************/
/* Scale */
/**********************************************/
mat3 const& transform::get_matrix() const
{
  if(p_is_dirty)
  {
    mat3 scale = mat3mk(
      p_scale[0], 0.0f, 0.0f,
      0.0f, p_scale[1], 0.0f,
      0.0f, 0.0f, 1.0f);
    vec2 dir = get_dir();
    mat3 rotate = mat3mk(
      dir.x(), -dir.y(), 0.0f,
      dir.y(), dir.x(), 0.0f,
      0.0f, 0.0f, 1.0f);
    mat3 translate = mat3mk(
      1.0f, 0.0f, p_pos[0],
      0.0f, 1.0f, p_pos[1],
      0.0f, 0.0f, 1.0f);

    p_mat = translate * rotate * scale;

    p_is_dirty = false;
  }

  return p_mat;
}

void transform::mark_as_dirty() const
{
  p_is_dirty = true;
}

void transform::mark_as_clean() const
{
  p_is_dirty = false;
}

void transform::set_rot(float value)
{
  mark_as_dirty();
  p_rot = value;
}

void transform::rotate(float rads)
{
  mark_as_dirty();
  p_rot += rads;
}

void transform::set_dir(vec2 const& value)
{
  mark_as_dirty();
  LE_FATAL_ERROR_IF(length(value) > 1.0f + epsilon, "Dir must be a unit length vector!");
  p_rot = acos(value.x());
  if(value.y() < 0.0f)
    p_rot = -p_rot;
}

} // namespace LE
