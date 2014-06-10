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
