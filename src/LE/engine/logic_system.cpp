/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "logic_system.h"

#include <LE/engine/entity.h>
#include <LE/engine/logic_component_base.h>

namespace LE
{

void logic_system::update(space & target, float dt)
{
  for(auto logic_comp_it = target.logic_component_begin<logic_component_base>();
      logic_comp_it != target.logic_component_end<logic_component_base>();
      ++logic_comp_it)
  {
    (*logic_comp_it)->update(dt);
  }
}

} // namespace LE
