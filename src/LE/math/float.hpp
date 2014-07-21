/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include <algorithm>
#include <type_traits>

namespace LE
{

template<typename FLOAT_T>
bool
is_equal_epsilon(
  FLOAT_T lhs,
  FLOAT_T rhs,
  FLOAT_T epsilon)
{
  static_assert(std::is_floating_point<FLOAT_T>::value, "Only floating point values may be used.");
  return (lhs >= (rhs - epsilon)) && (lhs <= (rhs + epsilon));
}

template<typename T>
T const&
min(
  T const& lhs,
  T const& rhs)
{
  return std::min(lhs, rhs);
}

template<typename T>
T const&
max(
  T const& lhs,
  T const& rhs)
{
  return std::max(lhs, rhs);
}

template<typename T>
T const&
clamp(
  T const& val,
  T const& min,
  T const& max)
{
  return min(max(val, min), max);
}


} // namespace LE
