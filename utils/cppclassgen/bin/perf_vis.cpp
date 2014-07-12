/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "perf_vis.h"

namespace LE
{

unique_id<logic_base> const perf_vis::type_id;

perf_vis::perf_vis(entity & owner) :
  logic_component_base(owner)
{
  
}

} // namespace LE
