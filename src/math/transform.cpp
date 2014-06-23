/*
************************************************************************************************
Copyright 2014 Peter Clark

This file is part of Lifeline Engine.

Lifeline Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Lifeline Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Lifeline Engine.  If not, see <http://www.gnu.org/licenses/>.
************************************************************************************************
*/

#include "transform.h"

namespace LE
{

/**********************************************/
/* Position */
/**********************************************/
void transform::set_pos(float x, float y)
{
  p_pos.set({x, y});
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
  return translate(vec2mk(x, y));
}

vec2 const& transform::translate(vec2 const& value)
{
  mark_as_dirty();
  return p_pos += value;
}

/**********************************************/
/* Scale */
/**********************************************/
void transform::set_scale(float x, float y)
{
  p_scale.set({x, y});
  mark_as_dirty();
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
  return scale_by(vec2mk(x, y));
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
    p_mat = mat3mk(
      p_scale[0], 0.0f, p_pos[0],
      0.0f, p_scale[1], p_pos[1],
      0.0f, 0.0f, 1.0f
    );

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

} // namespace LE
