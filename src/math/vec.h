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

#ifndef LE_MATH_VEC_H
#define LE_MATH_VEC_H

#include <array>
#include <type_traits>

namespace LE
{

template<size_t N, typename COMP_T = float>
struct vecn
{
  static_assert(std::is_floating_point<COMP_T>::value || std::is_integral<COMP_T>::value,
    "Only integral or floating point types may be used as components!");

  typedef COMP_T comp_t;

  vecn();
  explicit vecn(std::array<COMP_T, N> const& values);

  void set(std::array<COMP_T, N> const& values);

  COMP_T & operator[](size_t index);
  COMP_T const& operator[](size_t index) const;

  static size_t const size = N;

  COMP_T data[size];
};

typedef vecn<2> vec2;
typedef vecn<3> vec3;
typedef vecn<4> vec4;

/**********************************************************************************************/
/* Vector Arithmatic Operators */
/**********************************************************************************************/

/**********************************************/
/* Addition & Subtraction */
/**********************************************/

template<size_t N, typename COMP_T>
vecn<N, COMP_T>
operator+(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs);

template<size_t N, typename COMP_T>
vecn<N, COMP_T> &
operator+=(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs);

template<size_t N, typename COMP_T>
vecn<N, COMP_T>
operator-(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs);

template<size_t N, typename COMP_T>
vecn<N, COMP_T> &
operator-=(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs);

/**********************************************/
/* Piecewise Multiplication & Division */
/**********************************************/

template<size_t N, typename COMP_T>
vecn<N, COMP_T>
operator*(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs);


template<size_t N, typename COMP_T>
vecn<N, COMP_T> &
operator*=(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs);

template<size_t N, typename COMP_T>
vecn<N, COMP_T>
operator/(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs);


template<size_t N, typename COMP_T>
vecn<N, COMP_T> &
operator/=(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs);

/**********************************************************************************************/
/* Scalar  Arithmatic Operators */
/**********************************************************************************************/

/**********************************************/
/* Multiplication & Division */
/**********************************************/

template<size_t N, typename COMP_T>
vecn<N, COMP_T>
operator*(
  vecn<N, COMP_T> const& lhs,
  COMP_T rhs);

template<size_t N, typename COMP_T>
vecn<N, COMP_T> &
operator*=(
  vecn<N, COMP_T> const& lhs,
  COMP_T rhs);

template<size_t N, typename COMP_T>
vecn<N, COMP_T>
operator/(
  vecn<N, COMP_T> const& lhs,
  COMP_T rhs);

template<size_t N, typename COMP_T>
vecn<N, COMP_T> &
operator/=(
  vecn<N, COMP_T> const& lhs,
  COMP_T rhs);

/**********************************************************************************************/
/* Vector Operations */
/**********************************************************************************************/

template<size_t N, typename COMP_T>
COMP_T
dot(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs);

// Only valid for 3D
template<typename COMP_T>
vecn<3, COMP_T>
cross(
  vecn<3, COMP_T> const& lhs,
  vecn<3, COMP_T> const& rhs);

template<size_t N, typename COMP_T>
COMP_T
length(
  vecn<N, COMP_T> const& v);

template<size_t N, typename COMP_T>
COMP_T
length_sq(
  vecn<N, COMP_T> const& v);

template<size_t N, typename COMP_T>
vecn<N, COMP_T> &
normalize(
  vecn<N, COMP_T> & v);

template<size_t N, typename COMP_T>
vecn<N, COMP_T>
get_normalized(
  vecn<N, COMP_T> const& v);

} // namespace LE

#include "vec.hpp"

#endif // LE_MATH_VEC_H
