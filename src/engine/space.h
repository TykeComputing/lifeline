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
  /**********************************************/
  /* Entity Management */
  /**********************************************/
  typedef std::unordered_map<
    unique_id<entity>::value_type,
    std::unique_ptr<entity> > entity_owning_container;

  typedef std::vector<std::unique_ptr<component_base>> component_type_container;

  typedef std::unordered_map<
    unique_id<component_base>::value_type,
    component_type_container > component_owning_container;

  entity * create_entity(std::string const& name);

  entity * find_entity(std::string const& name);
  entity * find_entity(unique_id<entity> const& id);

  entity_owning_container::iterator entity_begin() { return p_entities.begin(); }
  entity_owning_container::const_iterator entity_cbegin() const { return p_entities.cbegin(); }
  entity_owning_container::iterator entity_end() { return p_entities.end(); }
  entity_owning_container::const_iterator entity_cend() const { return p_entities.cend(); }

  size_t entity_num() const { return p_entities.size(); }

  void remove_dead();

private:
  entity_owning_container p_entities;

   component_owning_container p_components;
};

} // namespace LE

#endif // LE_ENGINE_SPACE_H
