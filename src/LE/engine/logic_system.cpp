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
  // Since logic components may add more logic components we need to iterate over a temporary
  //   vector (since in case of vector growth all iterators would be invalidated).
  // NOTE - Purposefully not updating entities created this frame until next frame.
  std::vector<logic_component_base *> to_update(
    target.logic_component_begin<logic_component_base>(),
    target.logic_component_end<logic_component_base>());

  for(auto * curr_logic_comp : to_update)
  {
    curr_logic_comp->update(dt);
  }
}

} // namespace LE
