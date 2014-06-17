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
