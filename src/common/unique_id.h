/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_UNIQUE_ID_H
#define LE_COMMON_UNIQUE_ID_H

#include <functional>

#include <common/macros.h>

namespace LE
{

namespace internal
{

class global_scope
{
};

}
/*
 * SCOPE_T limits the uniqueness of an id to a given type.
 * This allows class A and class B to have overlapping unique_ids.
 *
 * Knowledge of the algorithm used to generate the ids should not be relied upon or used.
 *  (i.e. no guarantee of order or contiguousness is given)
 */
template<typename SCOPE_T = internal::global_scope>
class unique_id
{
public:
  LE_NON_COPYABLE(unique_id)

  typedef SCOPE_T scope;
  typedef size_t value_type;

  unique_id();

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
