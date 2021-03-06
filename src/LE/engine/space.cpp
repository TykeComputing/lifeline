/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "space.h"

#include <LE/common/logging.h>
#include <LE/engine/engine.h>
#include <LE/engine/transform_component.h>

namespace LE
{

void space::component_registrar::register_engine_component(
  space * s,
  unique_id<engine_component_base>::value_type type_id,
  engine_component_base * comp)
{
  s->p_register_engine_component(type_id, comp);
}

void space::component_registrar::unregister_engine_component(
  space * s,
  unique_id<engine_component_base>::value_type type_id,
  engine_component_base * comp)
{
  s->p_unregister_engine_component(type_id, comp);
}

void space::component_registrar::register_logic_component(
  space * s,
  unique_id<logic_component_base>::value_type type_id,
  logic_component_base * comp)
{
  s->p_register_logic_component(type_id, comp);
}

void space::component_registrar::unregister_logic_component(
  space * s,
  unique_id<logic_component_base>::value_type type_id,
  logic_component_base * comp)
{
  s->p_unregister_logic_component(type_id, comp);
}

space::space(std::string const& name) :
  p_name(name)
{

}

space::~space()
{
  // Entities reference space, thus we must clear them before deleting anything else in space.
  p_entities.clear();
}

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
      log_status(log_scope::ENGINE,
        "Creating entity named \"{}\", {} entities now in space \"{}\".",
          new_ent->get_name(),
          p_entities.size(),
          p_name);

      new_ent->set_owner(this);
      new_ent->create_component<transform_component>();
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

entity * space::find_entity(unique_id<entity>::value_type id)
{
  auto find_it = p_entities.find(id);
  if(find_it != p_entities.end())
  {
    return (*find_it).second.get();
  }
  else
  {
    return nullptr;
  }
}

void space::remove_dead_entities()
{
  for(auto it = p_entities.begin(); it != p_entities.end();)
  {
    if((*it).second->get_is_alive() == false)
    {
      log_status(log_scope::ENGINE,
        "Removing dead entity named \"{}\", {} entities now in space \"{}\".",
          (*it).second->get_name(),
          p_entities.size() - 1, // don't count entity being removed
          p_name);

      it = p_entities.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

/**********************************************/
/* Debug Drawing */
/**********************************************/

void space::clear_ddraw()
{
  m_world_ddraw.clear();
  m_hud_ddraw.clear();
}

/**********************************************/
/* Lifespan */
/**********************************************/

void space::kill()
{
  p_is_alive = false;
}

/**********************************************/
/* Utility */
/**********************************************/

engine * space::get_owning_engine()
{
  return p_owner;
}

engine const* space::get_owning_engine() const
{
  return p_owner;
}

void space::p_set_owner(engine * new_owner)
{
  p_owner = new_owner;
}

void space::set_is_active(bool value)
{
  p_is_active = value;
}

bool space::get_is_active() const
{
  return p_is_active;
}

std::string const& space::get_name() const
{
  return p_name;
}

void space::p_register_engine_component(
  unique_id<engine_component_base>::value_type type_id,
  engine_component_base * comp)
{
  LE_FATAL_ERROR_IF(type_id == engine_component_base::type_id.value(),
    "Cannot register base componet.")

  p_engine_components[type_id].emplace_back(comp);
}

void space::p_unregister_engine_component(
  unique_id<engine_component_base>::value_type type_id,
  engine_component_base * comp)
{
  LE_FATAL_ERROR_IF(type_id == engine_component_base::type_id.value(),
    "Cannot unregister base componet.")

  auto & container = p_engine_components[type_id];
  auto find_it = std::find(container.begin(), container.end(), comp);
  if(find_it != container.end())
  {
    std::swap(*find_it, container.back());
    container.pop_back();
  }
  else
  {
    LE_FATAL_ERROR("Attempting to unregister engine component that is not registered!");
  }
}

void space::p_register_logic_component(
  unique_id<logic_component_base>::value_type type_id,
  logic_component_base * comp)
{
  LE_FATAL_ERROR_IF(type_id == logic_component_base::type_id.value(),
    "Cannot register base componet.")

  // Add to aggregate container
  p_logic_components[logic_component_base::type_id.value()].emplace_back(comp);
  // Add to type specific container
  p_logic_components[type_id].emplace_back(comp);
}

void space::p_unregister_logic_component(
  unique_id<logic_component_base>::value_type type_id,
  logic_component_base * comp)
{
  LE_FATAL_ERROR_IF(type_id == engine_component_base::type_id.value(),
    "Cannot unregister base componet.")

  auto unregister_logic_component_type = [&](
    unique_id<logic_component_base>::value_type target_type_id)
  {
    auto & container = p_logic_components[target_type_id];
    auto find_it = std::find(container.begin(), container.end(), comp);
    if(find_it != container.end())
    {
      std::swap(*find_it, container.back());
      container.pop_back();
    }
    else
    {
      LE_FATAL_ERROR("Attempting to unregister logic component that is not registered!");
    }
  };

  // Remove from type specific container
  unregister_logic_component_type(type_id);
  // Remove from aggregate container
  unregister_logic_component_type(logic_component_base::type_id.value());
}

} // namespace LE
