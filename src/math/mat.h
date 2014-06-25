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

#ifndef LE_MATH_MAT_H
#define LE_MATH_MAT_H

#include <array>
#include <type_traits>

namespace LE
{

// N x N matrix
template<size_t N, typename COMP_T = float>
struct matn
{
  static_assert(std::is_floating_point<COMP_T>::value || std::is_integral<COMP_T>::value,
    "Only integral or floating point types may be used as components.");

  typedef COMP_T comp_t;

  matn();
  matn(std::array<COMP_T, N * N> const& values);

  void set(std::array<COMP_T, N * N> const& values);

  COMP_T & operator()(size_t row, size_t column);
  COMP_T const& operator()(size_t row, size_t column) const;

  COMP_T & operator[](size_t index);
  COMP_T const& operator[](size_t index) const;

  static size_t const num_rows = N;
  static size_t const num_cols = N;
  static size_t const size = N * N;

  COMP_T data[size];
};

typedef matn<2> mat2;
typedef matn<3> mat3;
typedef matn<4> mat4;

extern mat3 const identity_mat3;

/**********************************************************************************************/
/* Creation functions */
/**********************************************************************************************/

template<typename COMP_T = float>
matn<3, COMP_T> 
mat3mk(
  COMP_T m00, COMP_T m01, COMP_T m02,
  COMP_T m10, COMP_T m11, COMP_T m12,
  COMP_T m20, COMP_T m21, COMP_T m22);

template<typename COMP_T = float>
matn<4, COMP_T> 
mat4mk(
  COMP_T m00, COMP_T m01, COMP_T m02, COMP_T m03,
  COMP_T m10, COMP_T m11, COMP_T m12, COMP_T m13,
  COMP_T m20, COMP_T m21, COMP_T m22, COMP_T m23,
  COMP_T m30, COMP_T m31, COMP_T m32, COMP_T m33);

/**********************************************************************************************/
/* Matrix Arithmetic Operators */
/**********************************************************************************************/

template<typename COMP_T>
matn<3, COMP_T>
operator*(
  matn<3, COMP_T> const& lhs,
  matn<3, COMP_T> const& rhs);

template<typename COMP_T>
matn<3, COMP_T> &
operator*=(
  matn<3, COMP_T> & lhs,
  matn<3, COMP_T> const& rhs);

} // namespace LE

#include "mat.hpp"

#endif // LE_MATH_MAT_H
