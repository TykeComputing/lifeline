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

#ifndef LE_COMMON_UNIQUE_ID_H
#define LE_COMMON_UNIQUE_ID_H

#include <functional>

namespace LE
{

namespace detail
{

class global_scope
{
};

}
// SCOPE_T limits the uniqueness of an id to a given type.
//   This allows class A and class B to have overlapping unique_ids, which could be desirable
//   if these classes will never cross reference eachothers IDs.
//
// Knowledge of the algorithm used to generate the ids should not be relied upon or used.
//   (i.e. no guarantee of order or contiguousness is given)

template<typename SCOPE_T = detail::global_scope>
class unique_id
{
public:
  typedef SCOPE_T scope;
  typedef size_t value_type;

  unique_id();

  // TODO: Consider adding relational opertors instead?
//  operator value_type() const;

  value_type value() const
  {
    return p_value;
  }

  bool operator==(unique_id const& rhs) const
  {
    return p_value == rhs.p_value;
  }

private:
  value_type const p_value;

  static value_type get_next();
};

} // namespace LE

namespace std
{
  template<typename SCOPE_T>
  struct hash<LE::unique_id<SCOPE_T>>
  {
    typedef LE::unique_id<SCOPE_T> argument_type;
    typedef size_t value_type;

    value_type operator()(argument_type const& arg) const
    {
      return std::hash<size_t>()(arg.value());
    }
  };
}

#include "unique_id.hpp"

#endif // LE_COMMON_UNIQUE_ID_H
