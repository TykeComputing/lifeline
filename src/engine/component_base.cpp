/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "component_base.h"

#include <engine/entity.h>

namespace LE
{

entity const* component_base::get_owning_entity() const
{
  return p_owner;
}

entity * component_base::get_owning_entity()
{
  return p_owner;
}

void component_base::set_owner(entity * new_owner)
{
  p_owner = new_owner;
}

} // namespace LE
