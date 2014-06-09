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

#include "component_base.h"

#include <engine/entity.h>

namespace LE
{

component_base::component_base() :
  p_owner(nullptr)
{
  
}

entity const* component_base::get_owner() const
{
  return p_owner;
}

entity * component_base::get_owner()
{
  return p_owner;
}

void component_base::set_owner(entity * new_owner)
{
  p_owner = new_owner;
}

} // namespace LE
