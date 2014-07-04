/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include <cmath>
#include <type_traits>

#include <math/float.h>

namespace LE
{

template<size_t N, typename COMP_T>
vecn<N, COMP_T>::vecn()
{
  // Do nothing
}

// Likely too expensive for something as commonly used as a vector, will worry about later.
template<size_t N, typename COMP_T>
vecn<N, COMP_T>::vecn(std::array<COMP_T, size> const& values)
{
  set(values);
}

template<size_t N, typename COMP_T>
void vecn<N, COMP_T>::set(std::array<COMP_T, size> const& values)
{
  auto values_it = std::begin(values);
  for(auto data_it = std::begin(data); data_it != std::end(data); ++data_it)
  {
    *data_it = *values_it;
    ++values_it;
  }
}

template<size_t N, typename COMP_T>
COMP_T & vecn<N, COMP_T>::operator[](size_t index)
{
  return data[index];
}

template<size_t N, typename COMP_T>
COMP_T const& vecn<N, COMP_T>::operator[](size_t index) const
{
  return data[index];
}

/**********************************************************************************************/
/* Specializations */
/**********************************************************************************************/

/**********************************************/
/* vec2 */
/**********************************************/

template<typename COMP_T>
vecn<2, COMP_T>::vecn()
{
  // Do nothing
}

// Likely too expensive for something as commonly used as a vector, will worry about later.
template<typename COMP_T>
vecn<2, COMP_T>::vecn(COMP_T x, COMP_T y)
{
  set(x, y);
}

template<typename COMP_T>
void vecn<2, COMP_T>::set(COMP_T x, COMP_T y)
{
  data[0] = x;
  data[1] = y;
}

template<typename COMP_T>
COMP_T & vecn<2, COMP_T>::operator[](size_t index)
{
  return data[index];
}

template<typename COMP_T>
COMP_T const& vecn<2, COMP_T>::operator[](size_t index) const
{
  return data[index];
}

/**********************************************/
/* vec3 */
/**********************************************/

template<typename COMP_T>
vecn<3, COMP_T>::vecn()
{
  // Do nothing
}

// Likely too expensive for something as commonly used as a vector, will worry about later.
template<typename COMP_T>
vecn<3, COMP_T>::vecn(COMP_T x, COMP_T y, COMP_T z)
{
  set(x, y, z);
}

template<typename COMP_T>
void vecn<3, COMP_T>::set(COMP_T x, COMP_T y, COMP_T z)
{
  data[0] = x;
  data[1] = y;
  data[2] = z;
}

template<typename COMP_T>
COMP_T & vecn<3, COMP_T>::operator[](size_t index)
{
  return data[index];
}

template<typename COMP_T>
COMP_T const& vecn<3, COMP_T>::operator[](size_t index) const
{
  return data[index];
}

/**********************************************/
/* vec4 */
/**********************************************/

template<typename COMP_T>
vecn<4, COMP_T>::vecn()
{
  // Do nothing
}

// Likely too expensive for something as commonly used as a vector, will worry about later.
template<typename COMP_T>
vecn<4, COMP_T>::vecn(COMP_T x, COMP_T y, COMP_T z, COMP_T w)
{
  set(x, y, z, w);
}

template<typename COMP_T>
void vecn<4, COMP_T>::set(COMP_T x, COMP_T y, COMP_T z, COMP_T w)
{
  data[0] = x;
  data[1] = y;
  data[2] = z;
  data[3] = w;
}

template<typename COMP_T>
COMP_T & vecn<4, COMP_T>::operator[](size_t index)
{
  return data[index];
}

template<typename COMP_T>
COMP_T const& vecn<4, COMP_T>::operator[](size_t index) const
{
  return data[index];
}

/**********************************************************************************************/
/* Creation functions */
/**********************************************************************************************/

template<typename COMP_T>
vecn<2, COMP_T> vec2mk(COMP_T x, COMP_T y)
{
  vecn<2, COMP_T> v;
  v[0] = x;
  v[1] = y;
  return v;
}

template<typename COMP_T>
vecn<3, COMP_T> vec3mk(COMP_T x, COMP_T y, COMP_T z)
{
  vecn<3, COMP_T> v;
  v[0] = x;
  v[1] = y;
  v[2] = z;
  return v;
}

template<typename COMP_T>
vecn<4, COMP_T> vec4mk(COMP_T x, COMP_T y, COMP_T z, COMP_T w)
{
  vecn<4, COMP_T> v;
  v[0] = x;
  v[1] = y;
  v[2] = z;
  v[3] = w;
  return v;
}

//template<typename COMP_T>
//vecn<2, COMP_T>
//vec2mk(COMP_T x, COMP_T y)
//{
//  vecn<2, COMP_T> v;
//  set(v, x, y);
//  return v;
//}
//
//template<typename COMP_T>
//vecn<3, COMP_T>
//vec3mk(COMP_T x, COMP_T y, COMP_T z)
//{
//  vecn<3, COMP_T> v;
//  set(v, x, y, z);
//  return v;
//}
//
//template<typename COMP_T>
//vecn<4, COMP_T>
//vec4mk(COMP_T x, COMP_T y, COMP_T z, COMP_T w)
//{
//  vecn<4, COMP_T> v;
//  set(v, x, y, z, w);
//  return v;
//}

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
  vecn<N, COMP_T> const& rhs)
{
  vecn<N, COMP_T> result;
  for(size_t i = 0; i < N; ++i)
  {
    result[i] = lhs[i] + rhs[i];
  }
  return result;
}

template<size_t N, typename COMP_T>
vecn<N, COMP_T> &
operator+=(
  vecn<N, COMP_T> & lhs,
  vecn<N, COMP_T> const& rhs)
{
  for(size_t i = 0; i < N; ++i)
  {
    lhs[i] += rhs[i];
  }
  return lhs;
}

template<size_t N, typename COMP_T>
vecn<N, COMP_T>
operator-(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs)
{
  vecn<N, COMP_T> result;
  for(size_t i = 0; i < N; ++i)
  {
    result[i] = lhs[i] - rhs[i];
  }
  return result;
}

template<size_t N, typename COMP_T>
vecn<N, COMP_T> &
operator-=(
  vecn<N, COMP_T> & lhs,
  vecn<N, COMP_T> const& rhs)
{
  for(size_t i = 0; i < N; ++i)
  {
    lhs[i] -= rhs[i];
  }
  return lhs;
}

/**********************************************/
/* Piecewise Multiplication & Division */
/**********************************************/

template<size_t N, typename COMP_T>
vecn<N, COMP_T>
operator*(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs)
{
  vecn<N, COMP_T> result;
  for(size_t i = 0; i < N; ++i)
  {
    result[i] = lhs[i] * rhs[i];
  }
  return result;
}


template<size_t N, typename COMP_T>
vecn<N, COMP_T> &
operator*=(
  vecn<N, COMP_T> & lhs,
  vecn<N, COMP_T> const& rhs)
{
  for(size_t i = 0; i < N; ++i)
  {
    lhs[i] *= rhs[i];
  }
  return lhs;
}

template<size_t N, typename COMP_T>
vecn<N, COMP_T>
operator/(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs)
{
  vecn<N, COMP_T> result;
  for(size_t i = 0; i < N; ++i)
  {
    result[i] = lhs[i] / rhs[i];
  }
  return result;
}


template<size_t N, typename COMP_T>
vecn<N, COMP_T> &
operator/=(
  vecn<N, COMP_T> & lhs,
  vecn<N, COMP_T> const& rhs)
{
  for(size_t i = 0; i < N; ++i)
  {
    lhs[i] /= rhs[i];
  }
  return lhs;
}

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
  COMP_T rhs)
{
  vecn<N, COMP_T> result;
  for(size_t i = 0; i < N; ++i)
  {
    result[i] = lhs[i] * rhs;
  }
  return result;
}

template<size_t N, typename COMP_T>
vecn<N, COMP_T> &
operator*=(
  vecn<N, COMP_T> & lhs,
  COMP_T rhs)
{
  for(size_t i = 0; i < N; ++i)
  {
    lhs[i] *= rhs;
  }
  return lhs;
}

template<size_t N, typename COMP_T>
vecn<N, COMP_T>
operator/(
  vecn<N, COMP_T> const& lhs,
  COMP_T rhs)
{
  vecn<N, COMP_T> result;
  for(size_t i = 0; i < N; ++i)
  {
    result[i] = lhs[i] / rhs;
  }
  return result;
}

template<size_t N, typename COMP_T>
vecn<N, COMP_T> &
operator/=(
  vecn<N, COMP_T> & lhs,
  COMP_T rhs)
{
  for(size_t i = 0; i < N; ++i)
  {
    lhs[i] /= rhs;
  }
  return lhs;
}

/**********************************************************************************************/
/* Vector Operations */
/**********************************************************************************************/

template<size_t N, typename COMP_T>
COMP_T
dot(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs)
{
  COMP_T result = 0.0f;
  for(size_t i = 0; i < N; ++i)
  {
    result += lhs[i] * rhs[i];
  }
  return result;
}

// Only valid for 3D
template<typename COMP_T>
vecn<3, COMP_T>
cross(
  vecn<3, COMP_T> const& lhs,
  vecn<3, COMP_T> const& rhs)
{
  return {
    (lhs[1] * rhs[2]) - (lhs[2] * rhs[1]),
    (lhs[2] * rhs[0]) - (lhs[0] * rhs[2]),
    (lhs[0] * rhs[1]) - (lhs[1] * rhs[0])
  };
}

template<size_t N, typename COMP_T>
COMP_T
length(
  vecn<N, COMP_T> const& v)
{
  return std::sqrt(length_sq(v));
}

template<size_t N, typename COMP_T>
COMP_T
length_sq(
  vecn<N, COMP_T> const& v)
{
  return dot(v, v);
}

template<size_t N, typename COMP_T>
vecn<N, COMP_T> &
normalize(
  vecn<N, COMP_T> & v)
{
  COMP_T length;
  return normalize(v, length);
}

template<size_t N, typename COMP_T>
vecn<N, COMP_T> &
normalize(
  vecn<N, COMP_T> & v, COMP_T & old_length)
{
  old_length = length(v);
  for(size_t i = 0; i < N; ++i)
  {
    v[i] /= old_length;
  }
  return v;
}

template<size_t N, typename COMP_T>
vecn<N, COMP_T>
get_normalized(
  vecn<N, COMP_T> const& v)
{
  vecn<N, COMP_T> result{v};
  return normalize(result);
}

template<size_t N, typename COMP_T>
vecn<N, COMP_T>
get_normalized(
  vecn<N, COMP_T> const& v,
  COMP_T & old_length)
{
  vecn<N, COMP_T> result{ v };
  return normalize(result, old_length);
}

template<typename COMP_T>
vecn<2, COMP_T>
get_orthogonal(
  vecn<2, COMP_T> const& v)
{
  return vec2mk(v[1], -v[0]);
}

/**********************************************************************************************/
/* Relational Operations */
/**********************************************************************************************/

template<size_t N, typename COMP_T>
bool
operator==(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs)
{
  for(size_t i = 0; i < N; ++i)
  {
    if(lhs[i] != rhs[i])
    {
      return false;
    }
  }

  return true;
}

template<size_t N>
bool
operator==(
  vecn<N, float> const& lhs,
  vecn<N, float> const& rhs)
{
  for(size_t i = 0; i < N; ++i)
  {
    if(is_equal_epsilon<float>(lhs[i], rhs[i], epsilon) == false)
    {
      return false;
    }
  }

  return true;
}

template<size_t N>
bool
operator==(
  vecn<N, double> const& lhs,
  vecn<N, double> const& rhs)
{
  for(size_t i = 0; i < N; ++i)
  {
    if(is_equal_epsilon<double>(lhs[i], rhs[i], epsilon) == false)
    {
      return false;
    }
  }

  return true;
}

template<size_t N, typename COMP_T>
bool
operator!=(
  vecn<N, COMP_T> const& lhs,
  vecn<N, COMP_T> const& rhs)
{
  return !(lhs == rhs);
}

} // namespace LE
