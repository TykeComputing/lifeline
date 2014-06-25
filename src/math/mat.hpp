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

template<size_t N, typename COMP_T>
matn<N, COMP_T>::matn()
{
  // Do nothing
}

template<size_t N, typename COMP_T>
matn<N, COMP_T>::matn(std::array<COMP_T, N * N> const& values)
{
  set(values);
}

template<size_t N, typename COMP_T>
void 
matn<N, COMP_T>::set(std::array<COMP_T, N * N> const& values)
{
  auto values_it = std::begin(values);
  for(auto data_it = std::begin(data); data_it != std::end(data); ++data_it)
  {
    *data_it = *values_it;
    ++values_it;
  }
}

template<size_t N, typename COMP_T>
COMP_T &
matn<N, COMP_T>::operator()(
  size_t row,
  size_t column)
{
  return data[(row * num_cols) + column];
}

template<size_t N, typename COMP_T>
COMP_T const& 
matn<N, COMP_T>::operator()(
  size_t row,
  size_t col) const
{
  return data[(row * num_cols) + col];
}

template<size_t N, typename COMP_T>
COMP_T &
matn<N, COMP_T>::operator[](
  size_t index)
{
  return data[index];
}

template<size_t N, typename COMP_T>
COMP_T const& 
matn<N, COMP_T>::operator[](
  size_t index) const
{
  return data[index];
}

/**********************************************************************************************/
/* Creation functions */
/**********************************************************************************************/

template<typename COMP_T>
matn<3, COMP_T> 
mat3mk(
  COMP_T m00, COMP_T m01, COMP_T m02,
  COMP_T m10, COMP_T m11, COMP_T m12,
  COMP_T m20, COMP_T m21, COMP_T m22)
{
  return matn<3, COMP_T>({
    m00, m01, m02,
    m10, m11, m12,
    m20, m21, m22
  });
}

template<typename COMP_T>
matn<4, COMP_T>
mat4mk(
  COMP_T m00, COMP_T m01, COMP_T m02, COMP_T m03,
  COMP_T m10, COMP_T m11, COMP_T m12, COMP_T m13,
  COMP_T m20, COMP_T m21, COMP_T m22, COMP_T m23,
  COMP_T m30, COMP_T m31, COMP_T m32, COMP_T m33)
{
  return matn<4, COMP_T>({
    m00, m01, m02, m03,
    m10, m11, m12, m13,
    m20, m21, m22, m23,
    m30, m31, m32, m33
  });
}

/**********************************************************************************************/
/* Matrix Arithmetic Operators */
/**********************************************************************************************/

template<typename COMP_T>
matn<3, COMP_T>
operator*(
  matn<3, COMP_T> const& lhs,
  matn<3, COMP_T> const& rhs)
{
    return mat3({
    // -------------------------------------------------------------------
    //          1         |           2           |           3          |
    // row 0 -------------------------------------------------------------
    rhs(0, 0) * lhs(0, 0) + rhs(0, 1) * lhs(1, 0) + rhs(0, 2) * lhs(2, 0),  // 00
    rhs(0, 0) * lhs(0, 1) + rhs(0, 1) * lhs(1, 1) + rhs(0, 2) * lhs(2, 1),  // 01
    rhs(0, 0) * lhs(0, 2) + rhs(0, 1) * lhs(1, 2) + rhs(0, 2) * lhs(2, 2),  // 02
    // row 1 -------------------------------------------------------------
    rhs(1, 0) * lhs(0, 0) + rhs(1, 1) * lhs(1, 0) + rhs(1, 2) * lhs(2, 0),  // 10
    rhs(1, 0) * lhs(0, 1) + rhs(1, 1) * lhs(1, 1) + rhs(1, 2) * lhs(2, 1),  // 11
    rhs(1, 0) * lhs(0, 2) + rhs(1, 1) * lhs(1, 2) + rhs(1, 2) * lhs(2, 2),  // 12
    // row 2 -------------------------------------------------------------
    rhs(2, 0) * lhs(0, 0) + rhs(2, 1) * lhs(1, 0) + rhs(2, 2) * lhs(2, 0),  // 20
    rhs(2, 0) * lhs(0, 1) + rhs(2, 1) * lhs(1, 1) + rhs(2, 2) * lhs(2, 1),  // 21
    rhs(2, 0) * lhs(0, 2) + rhs(2, 1) * lhs(1, 2) + rhs(2, 2) * lhs(2, 2)}); // 22
}

template<typename COMP_T>
matn<3, COMP_T> const&
operator*=(
  matn<3, COMP_T> & lhs,
  matn<3, COMP_T> const& rhs)
{
  lhs = lhs * rhs;
  return lhs;
}

} // namespace LE
