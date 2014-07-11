/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
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
  explicit vecn(COMP_T fill_val);
  vecn(std::array<COMP_T, size> const& values);

  void set(std::array<COMP_T, size> const& values);

  COMP_T & operator[](size_t index);
  COMP_T const& operator[](size_t index) const;

  static vecn const zero;

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
  explicit vecn(COMP_T fill_val);
  vecn(COMP_T x, COMP_T y);

  vecn(vecn<3, COMP_T> const& rhs);
  vecn(vecn<4, COMP_T> const& rhs);

  void set(COMP_T x, COMP_T y);

  COMP_T & operator[](size_t index);
  COMP_T const& operator[](size_t index) const;

  inline COMP_T & x() { return data[0]; }
  inline COMP_T const& x() const { return data[0]; }
  inline COMP_T & y() { return data[1]; }
  inline COMP_T const& y() const { return data[1]; }

  static vecn const zero;

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
  explicit vecn(COMP_T fill_val);
  vecn(COMP_T x, COMP_T y, COMP_T z);

  vecn(vecn<2, COMP_T> const& rhs, COMP_T z);
  vecn(vecn<4, COMP_T> const& rhs);

  void set(COMP_T x, COMP_T y, COMP_T z);

  COMP_T & operator[](size_t index);
  COMP_T const& operator[](size_t index) const;

  inline COMP_T & x() { return data[0]; }
  inline COMP_T const& x() const { return data[0]; }
  inline COMP_T & y() { return data[1]; }
  inline COMP_T const& y() const { return data[1]; }
  inline COMP_T & z() { return data[2]; }
  inline COMP_T const& z() const { return data[2]; }

  static vecn const zero;

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
  explicit vecn(COMP_T fill_val);
  vecn(COMP_T x, COMP_T y, COMP_T z, COMP_T w);

  vecn(vecn<2, COMP_T> const& rhs, COMP_T z, COMP_T w);
  vecn(vecn<3, COMP_T> const& rhs, COMP_T w);

  void set(COMP_T x, COMP_T y, COMP_T z, COMP_T w);

  COMP_T & operator[](size_t index);
  COMP_T const& operator[](size_t index) const;

  inline COMP_T & x() { return data[0]; }
  inline COMP_T const& x() const { return data[0]; }
  inline COMP_T & y() { return data[1]; }
  inline COMP_T const& y() const { return data[1]; }
  inline COMP_T & z() { return data[2]; }
  inline COMP_T const& z() const { return data[2]; }
  inline COMP_T & w() { return data[3]; }
  inline COMP_T const& w() const { return data[3]; }

  static vecn const zero;

  COMP_T data[size];
};

typedef vecn<2> vec2;
typedef vecn<2, int> ivec2;
typedef vecn<2, unsigned> uvec2;
typedef vecn<3> vec3;
typedef vecn<3, int> ivec3;
typedef vecn<3, unsigned> uvec3;
typedef vecn<4> vec4;

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

/**********************************************************************************************/
/* Stream Operations */
/**********************************************************************************************/

template<size_t N, typename COMP_T>
std::ostream &
operator<<(
  std::ostream & os,
  vecn<N, COMP_T> const& rhs);


} // namespace LE

#include "vec.hpp"

#endif // LE_MATH_VEC_H
