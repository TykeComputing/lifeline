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

#ifndef LE_ENGINE_ENTITY_MANAGER_H
#define LE_ENGINE_ENTITY_MANAGER_H

#include <memory>
#include <vector>

#include <common/unique_id.h>

#include <engine/entity.h>

namespace LE
{

// TODO - UNHACK
class entity_manager
{
public:
  std::weak_ptr<entity> create_entity(std::string const& name);

  std::weak_ptr<entity> find_entity(std::string const& name);
  std::weak_ptr<entity> find_entity(unique_id<entity> const& id);

  void remove_dead();

  // TODO - Make private once systems have been added to engine
  std::unordered_map<unique_id<entity>, std::shared_ptr<entity>> p_entities;
private:
};

} // namespace LE

#endif // LE_ENGINE_ENTITY_MANAGER_H
