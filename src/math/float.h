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
