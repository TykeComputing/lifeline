/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_COMPONENT_BASE_H
#define LE_ENGINE_COMPONENT_BASE_H

#include <common/macros.h>
#include <common/unique_id.h>

namespace LE
{

class entity;
class space;

class component_base
{
public:
  component_base();
  virtual ~component_base() {}

  entity const* get_owner() const;
  entity * get_owner();

private:
  void set_owner(entity * new_owner);

  entity * p_owner = nullptr;

  friend class space;
};

} // namespace LE

#endif // LE_ENGINE_COMPONENT_BASE_H
