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
  static size_t const size = N;

  vecn();
  vecn(std::array<COMP_T, size> const& values);

  void set(std::array<COMP_T, size> const& values);

  COMP_T & operator[](size_t index);
  COMP_T const& operator[](size_t index) const;

  COMP_T data[size];
};

/**********************************************************************************************/
/* Specializations */
/**********************************************************************************************/

template<typename COMP_T>
struct vecn<2, COMP_T>
{
  static_assert(std::is_floating_point<COMP_T>::value || std::is_integral<COMP_T>::value,
    "Only integral or floating point types may be used as components!");

  typedef COMP_T comp_t;
  static size_t const size = 2;

  vecn();
  vecn(COMP_T x, COMP_T y);

  void set(COMP_T x, COMP_T y);

  COMP_T & operator[](size_t index);
  COMP_T const& operator[](size_t index) const;  

  COMP_T data[size];
};

template<typename COMP_T>
struct vecn<3, COMP_T>
{
  static_assert(std::is_floating_point<COMP_T>::value || std::is_integral<COMP_T>::value,
    "Only integral or floating point types may be used as components!");

  typedef COMP_T comp_t;
  static size_t const size = 3;

  vecn();
  vecn(COMP_T x, COMP_T y, COMP_T z);

  void set(COMP_T x, COMP_T y, COMP_T z);

  COMP_T & operator[](size_t index);
  COMP_T const& operator[](size_t index) const;

  COMP_T data[size];
};

template<typename COMP_T>
struct vecn<4, COMP_T>
{
  static_assert(std::is_floating_point<COMP_T>::value || std::is_integral<COMP_T>::value,
    "Only integral or floating point types may be used as components!");

  typedef COMP_T comp_t;
  static size_t const size = 4;

  vecn();
  vecn(COMP_T x, COMP_T y, COMP_T z, COMP_T w);

  void set(COMP_T x, COMP_T y, COMP_T z, COMP_T w);

  COMP_T & operator[](size_t index);
  COMP_T const& operator[](size_t index) const;  

  COMP_T data[size];
};

typedef vecn<2> vec2;
typedef vecn<3> vec3;
typedef vecn<4> vec4;

extern vec2 const zero_vec2;
extern vec3 const zero_vec3;
extern vec4 const zero_vec4;

/**********************************************************************************************/
/* Creation functions */
/**********************************************************************************************/

template<typename COMP_T = float>
vecn<2, COMP_T> 
vec2mk(COMP_T x, COMP_T y);

template<typename COMP_T = float>
vecn<3, COMP_T> 
vec3mk(COMP_T x, COMP_T y, COMP_T z);

template<typename COMP_T = float>
vecn<4, COMP_T> 
vec4mk(COMP_T x, COMP_T y, COMP_T z, COMP_T w);

/**********************************************************************************************/
/* Vector Arithmetic Operators */
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
/* Scalar Arithmetic Operators */
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
vecn<N, COMP_T> &
normalize(
  vecn<N, COMP_T> & v, COMP_T & old_length);

template<size_t N, typename COMP_T>
vecn<N, COMP_T>
get_normalized(
  vecn<N, COMP_T> const& v);

/*
 * 2D form
 * Will get an orthogonal vector of the form:
 *
 * (v)
 *  ^
 *  |
 *  |---> (result)
 *
 * Using this form to be analogous to the right hand rule (v is thumb, result is index)
 */
template<typename COMP_T>
vecn<2, COMP_T>
get_orthogonal(
  vecn<2, COMP_T> const& v);

/**********************************************************************************************/
/* Relational Operations */
/**********************************************************************************************/

template<size_t N, typename COMP_T>
bool
operator==(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs);

template<size_t N, typename COMP_T>
bool
operator!=(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs);

} // namespace LE

#include "vec.hpp"

#endif // LE_MATH_VEC_H
