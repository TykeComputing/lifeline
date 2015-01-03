/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_MATH_TRANSFORM_H
#define LE_MATH_TRANSFORM_H

#include <LE/math/mat.h>
#include <LE/math/vec.h>

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

  void set_scale(float val);
  void set_scale(float x, float y);
  void set_scale(vec2 const& value);
  void set_scale_x(float value);
  void set_scale_y(float value);

  vec2 const& scale_by(float value);
  vec2 const& scale_by(float x, float y);
  vec2 const& scale_by(vec2 const& value);

  /**********************************************/
  /* Orientation */
  /**********************************************/

  float get_rot() const { return p_rot; }
  vec2 get_dir() const { return vec2(cos(p_rot), sin(p_rot)); }
  vec2 get_right() const { return get_orthogonal(get_dir()); }

  void set_rot(float value) { p_rot = value; }
  void rotate(float rads) { p_rot += rads; }

  /**********************************************/
  /* Matrix */
  /**********************************************/
  mat3 const& get_matrix() const;

private:
  void mark_as_dirty() const;
  void mark_as_clean() const;

  vec2 p_pos = vec2::zero;
  float p_z_order = 0.0f;
  vec2 p_scale = vec2(1.0f, 1.0f);

  float p_rot = 0.0f;


  mutable mat3 p_mat;
  mutable bool p_is_dirty = true;
};

} // namespace LE

#endif // LE_MATH_TRANSFORM_H
