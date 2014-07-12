/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_LOGIC_COMPONENT_BASE_H
#define LE_ENGINE_LOGIC_COMPONENT_BASE_H

#include <engine/component_base.h>

namespace LE
{

class logic_component_base : public component_base
{
public:
  explicit logic_component_base(entity & owner);
  virtual ~logic_component_base() {}

  virtual void update(float dt) { LE_UNUSED_VAR(dt); }

private:
};

} // namespace LE

#endif // LE_ENGINE_LOGIC_COMPONENT_BASE_H
