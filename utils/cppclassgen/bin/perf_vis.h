/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_DEVUI_PERF_VIS_H
#define LE_DEVUI_PERF_VIS_H

#include <common/unique_id.h>

#include <engine/logic_component_base.h>

namespace LE
{

class perf_vis : public logic_component_base
{
public:
  perf_vis(entity & owner);
  virtual ~perf_vis() {}

  static unique_id<logic_component_base> const type_id;

private:
};

} // namespace LE

#endif // LE_DEVUI_PERF_VIS_H
