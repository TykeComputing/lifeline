/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_SCENE_BASE_H
#define LE_ENGINE_SCENE_BASE_H

#include <engine/component_base.h>

namespace LE
{

class logic_component_base : component_base
{
public:
  logic_component_base();
  virtual ~logic_component_base() {}

  virtual void initialize() {}
  virtual void update(float dt) { LE_UNUSED_VAR(dt); }
  virtual void teardown() {}

private:
};

} // namespace LE

#endif // LE_ENGINE_SCENE_BASE_H
