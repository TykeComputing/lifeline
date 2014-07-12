/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "transform_component.h"

namespace LE
{

unique_id<engine_component_base> const transform_component::type_id;

transform_component::transform_component(entity & owner) :
  engine_component_base(owner)
{
}

} // namespace LE
