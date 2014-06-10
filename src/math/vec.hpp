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

namespace LE
{

/**********************************************************************************************/
/* Vector Arithmatic Operators */
/**********************************************************************************************/

/**********************************************/
/* Addition & Subtraction */
/**********************************************/

template<size_t SIZE, typename COMP_T>
vecn<SIZE, COMP_T>
operator+(
  vecn<SIZE, COMP_T> const& lhs,
  vecn<SIZE, COMP_T> const& rhs)
{
  vecn<SIZE, COMP_T> result;
  for(size_t i = 0; i < SIZE; ++i)
  {
    result[i] = lhs[i] + rhs[i];
  }
  return result;
}

template<size_t SIZE, typename COMP_T>
vecn<SIZE, COMP_T> &
operator+=(
  vecn<SIZE, COMP_T> & lhs,
  vecn<SIZE, COMP_T> const& rhs)
{
  for(size_t i = 0; i < SIZE; ++i)
  {
    lhs[i] += rhs[i];
  }
  return lhs;
}

template<size_t SIZE, typename COMP_T>
vecn<SIZE, COMP_T>
operator-(
  vecn<SIZE, COMP_T> const& lhs,
  vecn<SIZE, COMP_T> const& rhs)
{
  vecn<SIZE, COMP_T> result;
  for(size_t i = 0; i < SIZE; ++i)
  {
    result[i] = lhs[i] - rhs[i];
  }
  return result;
}

template<size_t SIZE, typename COMP_T>
vecn<SIZE, COMP_T> &
operator-=(
  vecn<SIZE, COMP_T> & lhs,
  vecn<SIZE, COMP_T> const& rhs)
{
  for(size_t i = 0; i < SIZE; ++i)
  {
    lhs[i] -= rhs[i];
  }
  return lhs;
}

/**********************************************/
/* Piecewise Multiplication & Division */
/**********************************************/

template<size_t SIZE, typename COMP_T>
vecn<SIZE, COMP_T>
operator*(
  vecn<SIZE, COMP_T> const& lhs,
  vecn<SIZE, COMP_T> const& rhs)
{
  vecn<SIZE, COMP_T> result;
  for(size_t i = 0; i < SIZE; ++i)
  {
    result[i] = lhs[i] * rhs[i];
  }
  return result;
}


template<size_t SIZE, typename COMP_T>
vecn<SIZE, COMP_T> &
operator*=(
  vecn<SIZE, COMP_T> & lhs,
  vecn<SIZE, COMP_T> const& rhs)
{
  for(size_t i = 0; i < SIZE; ++i)
  {
    lhs[i] *= rhs[i];
  }
  return lhs;
}

template<size_t SIZE, typename COMP_T>
vecn<SIZE, COMP_T>
operator/(
  vecn<SIZE, COMP_T> const& lhs,
  vecn<SIZE, COMP_T> const& rhs)
{
  vecn<SIZE, COMP_T> result;
  for(size_t i = 0; i < SIZE; ++i)
  {
    result[i] = lhs[i] / rhs[i];
  }
  return result;
}


template<size_t SIZE, typename COMP_T>
vecn<SIZE, COMP_T> &
operator/=(
  vecn<SIZE, COMP_T> & lhs,
  vecn<SIZE, COMP_T> const& rhs)
{
  for(size_t i = 0; i < SIZE; ++i)
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

template<size_t SIZE, typename COMP_T>
vecn<SIZE, COMP_T>
operator*(
  vecn<SIZE, COMP_T> const& lhs,
  COMP_T rhs)
{
  vecn<SIZE, COMP_T> result;
  for(size_t i = 0; i < SIZE; ++i)
  {
    result[i] = lhs[i] * rhs;
  }
  return result;
}

template<size_t SIZE, typename COMP_T>
vecn<SIZE, COMP_T> &
operator*=(
  vecn<SIZE, COMP_T> & lhs,
  COMP_T rhs)
{
  for(size_t i = 0; i < SIZE; ++i)
  {
    lhs[i] *= rhs;
  }
  return lhs;
}

template<size_t SIZE, typename COMP_T>
vecn<SIZE, COMP_T>
operator/(
  vecn<SIZE, COMP_T> const& lhs,
  COMP_T rhs)
{
  vecn<SIZE, COMP_T> result;
  for(size_t i = 0; i < SIZE; ++i)
  {
    result[i] = lhs[i] / rhs;
  }
  return result;
}

template<size_t SIZE, typename COMP_T>
vecn<SIZE, COMP_T> &
operator/=(
  vecn<SIZE, COMP_T> & lhs,
  COMP_T rhs)
{
  for(size_t i = 0; i < SIZE; ++i)
  {
    lhs[i] /= rhs;
  }
  return lhs;
}

/**********************************************************************************************/
/* Vector Operations */
/**********************************************************************************************/

template<size_t SIZE, typename COMP_T>
COMP_T
dot(
  vecn<SIZE, COMP_T> const& lhs,
  vecn<SIZE, COMP_T> const& rhs)
{
  COMP_T result = 0.0f;
  for(size_t i = 0; i < SIZE; ++i)
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

template<size_t SIZE, typename COMP_T>
COMP_T
length(
  vecn<SIZE, COMP_T> const& v)
{
  return std::sqrt(length_sq(v));
}

template<size_t SIZE, typename COMP_T>
COMP_T
length_sq(
  vecn<SIZE, COMP_T> const& v)
{
  return dot(v, v);
}

template<size_t SIZE, typename COMP_T>
vecn<SIZE, COMP_T> &
normalize(
  vecn<SIZE, COMP_T> & v)
{
  COMP_T length;
  return normalize(v, length);
}

template<size_t SIZE, typename COMP_T>
vecn<SIZE, COMP_T> &
normalize(
  vecn<SIZE, COMP_T> & v, COMP_T & old_length)
{
  old_length = length(v);
  for(size_t i = 0; i < SIZE; ++i)
  {
    v[i] /= old_length;
  }
  return v;
}

template<size_t SIZE, typename COMP_T>
vecn<SIZE, COMP_T>
get_normalized(
  vecn<SIZE, COMP_T> const& v)
{
  vecn<SIZE, COMP_T> result{v};
  return normalize(result);
}

} // namespace LE
