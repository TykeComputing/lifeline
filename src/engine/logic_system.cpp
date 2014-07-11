/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "logic_system.h"

#include <engine/entity.h>
#include <engine/logic_component_base.h>

namespace LE
{

void logic_system::update(space & target, float dt)
{
  // Very primitive update loop
  // TODO - Improve (having array of logic components
  for(auto entity_it = target.entity_begin();
      entity_it != target.entity_end();
      ++entity_it)
  {
    auto & curr_ent = (*entity_it).second;
    for(auto logic_comp_it = curr_ent->logic_component_begin();
        logic_comp_it != curr_ent->logic_component_end();
        ++logic_comp_it)
    {
      auto & curr_logic_comp = (*logic_comp_it).second;
      curr_logic_comp->update(dt);
    }
  }
}

} // namespace LE
