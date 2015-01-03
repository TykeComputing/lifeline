/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "mat.h"

namespace LE
{

mat3 const identity_mat3 = mat3mk(
  1.f, 0.f, 0.f,
  0.f, 1.f, 0.f,
  0.f, 0.f, 1.f
);

/**********************************************************************************************/
/* Matrix Operations */
/**********************************************************************************************/


void transpose(mat3 & m)
{
  std::swap(m(1, 0), m(0, 1));
  std::swap(m(2, 0), m(0, 2));
  std::swap(m(1, 2), m(2, 1));
}

mat3 get_transpose(mat3 const& m)
{
  mat3 m_t = m;
  transpose(m_t);
  return m_t;
}

mat3 get_inverse(mat3 const& m)
{
  mat3 m_t = get_transpose(m);
  float a = m_t(0, 0);
  float b = m_t(0, 1);
  float c = m_t(0, 2);
  float d = m_t(1, 0);
  float e = m_t(1, 1);
  float f = m_t(1, 2);
  float g = m_t(2, 0);
  float h = m_t(2, 1);
  float i = m_t(2, 2);

  float det = ((a*e*i) + (b*f*g) + (c*d*h)) - ((c*e*g) + (b*d*i) + (a*f*h));
  LE_FATAL_ERROR_IF(det == 0.0f, "Non-invertable matrix being inverted!");

  // | a b c |
  // | d e f |
  // | g h i |

  // | a b |
  // | c d |
  // 2x2 det: ad - bc

  // inv = (1/det) * cofactor^T

  return (1.0f / det) * mat3mk(
    +(e*i - f*h),
    -(d*i - f*g),
    +(d*h - e*g),

    -(b*i - c*h),
    +(a*i - c*g),
    -(a*h - b*g),

    +(b*f - c*e),
    -(a*f - c*d),
    +(a*e - b*d)
  );
}

LE::mat4 mat4mk(mat3 const& m)
{
  return mat4mk(
    m(0, 0), m(0, 1), m(0, 2), 0.0f,
    m(1, 0), m(1, 1), m(1, 2), 0.0f,
    m(2, 0), m(2, 1), m(2, 2), 0.0f,
       0.0f,    0.0f,    0.0f, 1.0f);
}

}
