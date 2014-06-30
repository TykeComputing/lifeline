/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "transform_component.h"

namespace LE
{

unique_id<component_base> const transform_component::type_id;

transform_component::transform_component()
{
  set_scale(0.1f, 0.1f);
}

} // namespace LE
