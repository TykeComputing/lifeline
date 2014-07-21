/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_MATH_FLOAT_H
#define LE_MATH_FLOAT_H

namespace LE
{

template<typename FLOAT_T>
bool
is_equal_epsilon(
  FLOAT_T lhs,
  FLOAT_T rhs,
  FLOAT_T epsilon);

// TODO - Move/remove?
template<typename T>
T const&
min(
  T const& lhs,
  T const& rhs);

template<typename T>
T const&
max(
  T const& lhs,
  T const& rhs);

template<typename T>
T const&
clamp(
  T const& val,
  T const& min,
  T const& max);

extern float const pi;
extern float const epsilon;

} // namespace LE

#include "float.hpp"

#endif // LE_MATH_FLOAT_H
