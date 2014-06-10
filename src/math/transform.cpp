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
}

void transform::set_pos(vec2 const& value)
{
  set_pos(value[0], value[1]);
}

void transform::set_pos_x(float value)
{
  p_pos[0] = value;
}

void transform::set_pos_y(float value)
{
  p_pos[1] = value;
}

void transform::set_z_order(float value)
{
  p_z_order = value;
}

vec2 const& transform::translate(float x, float y)
{
  return translate(vec2({x, y}));
}

vec2 const& transform::translate(vec3 const& value)
{
  return p_pos += value;
}

/**********************************************/
/* Scale */
/**********************************************/
void transform::set_scale(float x, float y)
{
  p_scale.set({x, y});
}

void transform::set_scale(vec2 const& value)
{
  p_scale = value;
}

void transform::set_scale_x(float value)
{
  p_scale[0] = value;
}

void transform::set_scale_y(float value)
{
  p_scale[1] = value;
}

vec2 const& transform::scale_by(float value)
{
  return scale_by(value, value, value);
}

vec2 const& transform::scale_by(float x, float y)
{
  return scale_by(vec2({x, y}));
}

vec2 const& transform::scale_by(vec2 const& value)
{
  return p_pos *= value;
}

} // namespace LE
