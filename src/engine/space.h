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

#ifndef LE_ENGINE_SPACE_H
#define LE_ENGINE_SPACE_H

#include <memory>
#include <vector>

#include <common/unique_id.h>

#include <engine/component_base.h>
#include <engine/entity.h>

namespace LE
{

class space
{
public:
  entity * create_entity(std::string const& name);

  entity * find_entity(std::string const& name);
  entity * find_entity(unique_id<entity> const& id);

  void remove_dead();

//private:
  std::unordered_map<
    unique_id<entity>::value_type,
    std::unique_ptr<entity> > p_entities;

  std::unordered_map<
    unique_id<component_base>::value_type,
    std::vector<std::unique_ptr<component_base>> > p_components;
};

} // namespace LE

#endif // LE_ENGINE_SPACE_H
