/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_TRANSFORM_COMPONENT_H
#define LE_ENGINE_TRANSFORM_COMPONENT_H

#include <LE/math/transform.h>
#include <LE/math/vec.h>

#include <LE/engine/engine_component_base.h>

namespace LE
{

// TODO - Figure out how I'm going to handle transformation heirarchies and then decide on
//          final transform/transform_component design.
//      - Trying inheiritance based approch for now. I should evaluate if this is desirable
//          when implementing parenting. EVALUATED: When implementing parenting, do away with
//          inheiritance approach.
class transform_component : public engine_component_base, public transform
{
public:
  static unique_id<engine_component_base> const type_id;
};

} // namespace LE

#endif // LE_ENGINE_TRANSFORM_COMPONENT_H
