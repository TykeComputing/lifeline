/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
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

  void set_scale(float val);
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

  vec2 p_pos = vec2::zero;
  float p_z_order = 0.0f;
  vec2 p_scale = vec2(1.0f, 1.0f);

  // TODO - Rotation


  mutable mat3 p_mat;
  mutable bool p_is_dirty = true;
};

} // namespace LE

#endif // LE_MATH_TRANSFORM_H
