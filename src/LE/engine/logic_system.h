/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_LOGIC_SYSTEM_H
#define LE_ENGINE_LOGIC_SYSTEM_H

#include <LE/engine/space.h>

namespace LE
{

class logic_system
{
public:
  void update(space & target, float dt);

private:
};

} // namespace LE

#endif // LE_ENGINE_LOGIC_SYSTEM_H
