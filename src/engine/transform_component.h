/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_TRANSFORM_COMPONENT_H
#define LE_ENGINE_TRANSFORM_COMPONENT_H

#include <math/transform.h>
#include <math/vec.h>

#include <engine/component_base.h>

namespace LE
{

// TODO - Figure out how I'm going to handle transformation heirarchies and then decide on
//          final transform/transform_component design.
//      - Trying inheiritance based approch for now. I should evaluate if this is desirable
//          when implementing parenting.
class transform_component : public component_base, public transform
{
public:
  transform_component();

  static unique_id<component_base> const type_id;
};

} // namespace LE

#endif // LE_ENGINE_TRANSFORM_COMPONENT_H
