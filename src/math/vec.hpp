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
vecn<N, COMP_T>::vecn(std::array<COMP_T, N> const& values)
{
  set(values);
}

template<size_t N, typename COMP_T>
void vecn<N, COMP_T>::set(std::array<COMP_T, N> const& values)
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
/* Creation functions */
/**********************************************************************************************/
template<typename COMP_T>
vecn<2, COMP_T> vec2mk(COMP_T x, COMP_T y)
{
  vecn<2, comp_t> v;
  v[0] = x;
  v[1] = y;
  return v;
}

template<typename COMP_T>
vecn<3, COMP_T> vec3mk(COMP_T x, COMP_T y, COMP_T z)
{
  vecn<3, comp_t> v;
  v[0] = x;
  v[1] = y;
  v[2] = z;
  return v;
}

template<typename COMP_T>
vecn<4, COMP_T> vec4mk(COMP_T x, COMP_T y, COMP_T z, COMP_T w)
{
  vecn<3, comp_t> v;
  v[0] = x;
  v[1] = y;
  v[2] = z;
  v[3] = w;
  return v;
}

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
/* Scalar  Arithmatic Operators */
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

template<typename COMP_T>
vecn<2, COMP_T>
get_orthogonal(
  vecn<2, COMP_T> const& v)
{
  return vec2({ v[1], -v[0] });
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
