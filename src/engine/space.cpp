/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "space.h"

#include <common/logging.h>

#include <engine/sprite_component.h>
#include <engine/transform_component.h>

namespace LE
{

/**********************************************/
/* Entity Management */
/**********************************************/
entity * space::create_entity(std::string const& name)
{
  auto id_ent_pair = std::make_pair(0u, std::unique_ptr<entity>(new entity{name}));
  if(id_ent_pair.second)
  {
    // Set key to new entity's ID
    // TODO - Consider having space assign id instead.
    id_ent_pair.first = id_ent_pair.second->get_id().value();

    auto new_ent_emplace_result = p_entities.emplace(std::move(id_ent_pair));

    // Check result of emplace
    if(new_ent_emplace_result.second)
    {
      auto & new_ent = new_ent_emplace_result.first->second;

      log_status(log_scope::ENGINE, "Creating entity named \"{}\"", new_ent->get_name());

      new_ent->create_component<transform_component>();
      new_ent->create_component<sprite_component>();
      return new_ent.get();
    }
    else
    {
      LE_FATAL_ERROR("Unable to insert new entity into container, conflicting ID!");
      return nullptr;
    }
  }
  else
  {
    LE_FATAL_ERROR("Unable to create entity!");
    return nullptr;
  }
}

entity * space::find_entity(std::string const& name)
{
  for(auto & it : p_entities)
  {
    if(it.second->get_name() == name)
    {
      return it.second.get();
    }
  }

  return nullptr;
}

entity * space::find_entity(unique_id<entity> const& id)
{
  auto find_it = p_entities.find(id.value());
  if(find_it != p_entities.end())
  {
    return (*find_it).second.get();
  }
  else
  {
    return nullptr;
  }
}

void space::remove_dead()
{
  for(auto it = p_entities.begin(); it != p_entities.end();)
  {
    if((*it).second->is_alive() == false)
    {
      log_status(log_scope::ENGINE,
        "Removing dead entity named \"{}\"", (*it).second->get_name());

      it = p_entities.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

} // namespace LE