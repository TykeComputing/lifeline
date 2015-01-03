/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include <LE/common/fatal_error.h>

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
  LE_FATAL_ERROR_IF(row >= N || column >= N, "Invalid index!");
  return data[(row * num_cols) + column];
}

template<size_t N, typename COMP_T>
COMP_T const&
matn<N, COMP_T>::operator()(
  size_t row,
  size_t column) const
{
  LE_FATAL_ERROR_IF(row >= N || column >= N, "Invalid index!");
  return data[(row * num_cols) + column];
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
    lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0),  // 00
    lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1),  // 01
    lhs(0, 0) * rhs(0, 2) + lhs(0, 1) * rhs(1, 2) + lhs(0, 2) * rhs(2, 2),  // 02
    // row 1 -------------------------------------------------------------
    lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0),  // 10
    lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1),  // 11
    lhs(1, 0) * rhs(0, 2) + lhs(1, 1) * rhs(1, 2) + lhs(1, 2) * rhs(2, 2),  // 12
    // row 2 -------------------------------------------------------------
    lhs(2, 0) * rhs(0, 0) + lhs(2, 1) * rhs(1, 0) + lhs(2, 2) * rhs(2, 0),  // 20
    lhs(2, 0) * rhs(0, 1) + lhs(2, 1) * rhs(1, 1) + lhs(2, 2) * rhs(2, 1),  // 21
    lhs(2, 0) * rhs(0, 2) + lhs(2, 1) * rhs(1, 2) + lhs(2, 2) * rhs(2, 2)}); // 22
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

template<typename COMP_T>
vecn<3, COMP_T>
operator*(
  matn<3, COMP_T> const& lhs,
  vecn<3, COMP_T> const& rhs)
{
  return vec3({
    (lhs(0, 0) * rhs.x()) + (lhs(0, 1) * rhs.y()) + (lhs(0, 2) * rhs.z()), // x
    (lhs(1, 0) * rhs.x()) + (lhs(1, 1) * rhs.y()) + (lhs(1, 2) * rhs.z()), // y
    (lhs(2, 0) * rhs.x()) + (lhs(2, 1) * rhs.y()) + (lhs(2, 2) * rhs.z()) // z
  });
}

template<size_t N, typename COMP_T>
matn<N, COMP_T>
operator*(
  COMP_T scalar,
  matn<N, COMP_T> const& m)
{
  mat3 res;
  for(size_t i = 0; i < matn<N, COMP_T>::size; ++i)
  {
    res[i] = m[i] * scalar;
  }
  return res;
}



/**********************************************************************************************/
/* Conversions */
/**********************************************************************************************/

} // namespace LE
