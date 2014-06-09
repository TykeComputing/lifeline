/*
************************************************************************************************
Copyright 2014 Peter Clark

This file is part of Lifeline Engine.

Lifeline Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Lifeline Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Lifeline Engine.  If not, see <http://www.gnu.org/licenses/>.
************************************************************************************************
*/

#ifndef LE_ENGINE_COMPONENT_BASE_H
#define LE_ENGINE_COMPONENT_BASE_H

#include <common/macros.h>

namespace LE
{

// TODO - UNHACK & Search for find better solution
LE_ENUM_3(component_type,
  transform_component,
  sprite_component,
  logic_component);

class entity;

// TODO - UNHACK
class component_base
{
public:
  component_base();

  entity const* get_owner() const;
  entity * get_owner();

  virtual component_type::value get_type() = 0;

private:
  void set_owner(entity * new_owner);

  entity * p_owner;

  friend class entity_manager;
};

} // namespace LE

#endif // LE_ENGINE_COMPONENT_BASE_H
