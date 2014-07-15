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

class component_base
{
public:
  virtual ~component_base() {}

  entity const* get_owning_entity() const;
  entity * get_owning_entity();

private:
  void set_owner(entity * new_owner);

  entity * p_owner = nullptr;

  friend class entity;
};

} // namespace LE

#endif // LE_ENGINE_COMPONENT_BASE_H
