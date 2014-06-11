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

#include "entity_manager.h"

#include <common/LE_printf.h>

#include <engine/sprite_component.h>
#include <engine/transform_component.h>

namespace LE
{

std::weak_ptr<entity> entity_manager::create_entity(std::string const& name)
{
  auto new_ent = std::make_shared<entity>(name);
  auto new_ent_it = p_entities.emplace(std::make_pair(new_ent->get_id(), new_ent));
  if(new_ent_it.second)
  {
    new_ent->create_component<transform_component>();
    new_ent->create_component<sprite_component>();
    return new_ent_it.first->second;
  }
  else
  {
    LE_ERROR("Unable to create entity!");
    return {};
  }
}

// TODO: Add more debug printing to all functions.
std::weak_ptr<entity> entity_manager::find_entity(std::string const& name)
{
  for(auto & it : p_entities)
  {
    if(it.second->get_name() == name)
    {
      return it.second;
    }
  }

  return {};
}

bool entity_manager::remove_entity(std::weak_ptr<entity> target)
{
  auto owned_target = target.lock();
  if(owned_target)
  {
    auto result = remove_entity(owned_target->get_id());
    if(result == false)
    {
      // TODO - Print name
      LE_printf("Entity Manager: Unable to remove entity with name \"...\".");
    }

    return result;
  }

  LE_printf("Entity Manager: Unable to remove entity, no longer exists.");
  return false;
}

bool entity_manager::remove_entity(const unique_id<entity> & id)
{
  auto enemy_find_it = p_entities.find(id);
  if(enemy_find_it != p_entities.end())
  {
    p_entities.erase(enemy_find_it);
    return true;
  }
  else
  {
    LE_printf("Entity Manager: Unable to remove entity with id \"%d\".", id.value());
    return false;
  }
}

} // namespace LE
