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

namespace LE
{

template<size_t dim, typename comp_t>
class vec_t
{
public:
  comp_t & operator[](size_t index)
  {
    return data[index];
  }

  comp_t const& operator[](size_t index) const
  {
    return data[index];
  }

  static size_t const num_components = dim;

  comp_t data[num_components];
};

/**********************************************************************************************/
/* Vector Operations */
/**********************************************************************************************/

/**********************************************/
/* Addition & Subtraction */
/**********************************************/

template<size_t dim, typename comp_t>
vec_t<dim, comp_t> operator+(
  vec_t<dim, comp_t> const& lhs,
  vec_t<dim, comp_t> const& rhs)
{
  vec_t<dim, comp_t> result;
  for(size_t i = 0; i < dim; ++i)
  {
    result[i] = lhs[i] + rhs[i];
  }
  return result;
}

template<size_t dim, typename comp_t>
vec_t<dim, comp_t> const& operator+=(
  vec_t<dim, comp_t> const& lhs,
  vec_t<dim, comp_t> const& rhs)
{

  for(size_t i = 0; i < dim; ++i)
  {
    lhs[i] += rhs[i];
  }
  return lhs;
}

template<size_t dim, typename comp_t>
vec_t<dim, comp_t> operator-(
  vec_t<dim, comp_t> const& lhs,
  vec_t<dim, comp_t> const& rhs)
{
  vec_t<dim, comp_t> result;
  for(size_t i = 0; i < dim; ++i)
  {
    result[i] = lhs[i] - rhs[i];
  }
  return result;
}

template<size_t dim, typename comp_t>
vec_t<dim, comp_t> const& operator-=(
  vec_t<dim, comp_t> const& lhs,
  vec_t<dim, comp_t> const& rhs)
{
  for(size_t i = 0; i < dim; ++i)
  {
    lhs[i] -= rhs[i];
  }
  return lhs;
}

/**********************************************/
/* Piecewise Multiplication & Division */
/**********************************************/

template<size_t dim, typename comp_t>
vec_t<dim, comp_t> operator*(
  vec_t<dim, comp_t> const& lhs,
  vec_t<dim, comp_t> const& rhs)
{
  vec_t<dim, comp_t> result;
  for(size_t i = 0; i < dim; ++i)
  {
    result[i] = lhs[i] * rhs[i];
  }
  return result;
}

template<size_t dim, typename comp_t>
vec_t<dim, comp_t> const& operator*=(
  vec_t<dim, comp_t> const& lhs,
  vec_t<dim, comp_t> const& rhs)
{
  for(size_t i = 0; i < dim; ++i)
  {
    lhs[i] *= rhs[i];
  }
  return lhs;
}

template<size_t dim, typename comp_t>
vec_t<dim, comp_t> operator/(
  vec_t<dim, comp_t> const& lhs,
  vec_t<dim, comp_t> const& rhs)
{
  vec_t<dim, comp_t> result;
  for(size_t i = 0; i < dim; ++i)
  {
    result[i] = lhs[i] / rhs[i];
  }
  return result;
}

template<size_t dim, typename comp_t>
vec_t<dim, comp_t> const& operator/=(
  vec_t<dim, comp_t> const& lhs,
  vec_t<dim, comp_t> const& rhs)
{
  for(size_t i = 0; i < dim; ++i)
  {
    lhs[i] /= rhs[i];
  }
  return lhs;
}

/**********************************************************************************************/
/* Scalar Operations */
/**********************************************************************************************/

/**********************************************/
/* Multiplication & Division */
/**********************************************/

template<size_t dim, typename comp_t>
vec_t<dim, comp_t> operator*(
  vec_t<dim, comp_t> const& lhs,
  comp_t rhs)
{
  return {
    lhs.x * rhs,
    lhs.y * rhs
  };
}

template<size_t dim, typename comp_t>
vec_t<dim, comp_t> const& operator*=(
  vec_t<dim, comp_t> const& lhs,
  comp_t rhs)
{
  lhs.x *= rhs;
  lhs.y *= rhs;
  return *this;
}

template<size_t dim, typename comp_t>
vec_t<dim, comp_t> operator/(
  vec_t<dim, comp_t> const& lhs,
  comp_t rhs)
{
  return {
    lhs.x / rhs,
    lhs.y / rhs
  };
}

template<size_t dim, typename comp_t>
vec_t<dim, comp_t> const& operator/=(
  vec_t<dim, comp_t> const& lhs,
  comp_t rhs)
{
  lhs.x /= rhs;
  lhs.y /= rhs;
  return *this;
}

comp_t get_length() const
{
  return std::sqrt(get_length_sq());
}

comp_t get_length_sq() const
{
  return dot(*this, *this);
}

// Returns old length
comp_t normalize()
{
  comp_t length = get_length();
  x /= length;
  y /= length;

  return length;
}

template<typename comp_t>
float dot(vec_t<dim, comp_t> const& lhs, vec_t<dim, comp_t> const& rhs)
{
  return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}

template<typename comp_t>
float get_length(vec_t<dim, comp_t> const& lhs)
{
  return lhs.get_length();
}

template<typename comp_t>
float get_length_sq(vec_t<dim, comp_t> const& lhs)
{
  return lhs.get_length_sq();
}

typedef vec_t<float> vec2;

} // namespace LE

#include "vec.hpp"

#endif // LE_MATH_VEC_H
