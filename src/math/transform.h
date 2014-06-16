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

#ifndef LE_MATH_TRANSFORM_H
#define LE_MATH_TRANSFORM_H

#include <math/mat.h>
#include <math/vec.h>

namespace LE
{

class transform
{
public:
  /**********************************************/
  /* Position */
  /**********************************************/
  vec2 const& get_pos() const { return p_pos; }
  float get_pos_x() const { return p_pos[0]; }
  float get_pos_y() const { return p_pos[1]; }
  float get_z_order() const { return p_z_order; }

  void set_pos(float x, float y);
  void set_pos(vec2 const& value);
  void set_pos_x(float value);
  void set_pos_y(float value);
  void set_z_order(float value);

  vec2 const& translate(float x, float y);
  vec2 const& translate(vec2 const& value);

  /**********************************************/
  /* Scale */
  /**********************************************/
  vec2 const& get_scale() const { return p_scale; }
  float get_scale_x() const { return p_scale[0]; }
  float get_scale_y() const { return p_scale[1]; }

  void set_scale(float x, float y);
  void set_scale(vec2 const& value);
  void set_scale_x(float value);
  void set_scale_y(float value);

  vec2 const& scale_by(float value);
  vec2 const& scale_by(float x, float y);
  vec2 const& scale_by(vec2 const& value);

  /**********************************************/
  /* Matrix */
  /**********************************************/
  mat3 const& get_matrix() const;

private:
  void mark_as_dirty() const;
  void mark_as_clean() const;

  vec2 p_pos = zero_vec2;
  float p_z_order = 0.0f;
  vec2 p_scale = vec2({1.0f, 1.0f});

  // TODO - Rotation


  mutable mat3 p_mat;
  mutable bool p_is_dirty = true;
};

} // namespace LE

#endif // LE_MATH_TRANSFORM_H
