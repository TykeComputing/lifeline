5/*
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

space::space(std::string const& name) :
  p_name(name)
{

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

void space::kill_all()
{
  for(auto & it : p_entities)
  {
    it.second->kill();
  }
}

void space::remove_dead()
{
  for(auto it = p_entities.begin(); it != p_entities.end();)
  {
    if((*it).second->is_alive() == false)
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
/* Utility */
/**********************************************/
std::string const& space::get_name() const
{
  return p_name;
}

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

/*!
 * \brief For internal use only by entity, should not be manually called.
 * \todo Make private or refactor in some way?
 */
space::register_engine_component(COMP_T * comp)
{
  static_assert(std::is_base_of<engine_component_base, COMP_T>::value,
    "Cannot use with non-engine component!");
  static_assert(std::is_same<engine_component_base, COMP_T>::value == false,
    "Cannot get base component!");

  p_engine_components[COMP_T::type_id.value()].emplace_back(comp);
}

/*!
 * \brief For internal use only by entity, should not be manually called.
 * \note Should consider all iterators to engine components obtained from this space to be
 *   invalidated when called.
 * \todo Make private or refactor in some way?
 */
template<typename COMP_T>
void
space::unregister_engine_component(COMP_T * comp)
{
  static_assert(std::is_base_of<engine_component_base, COMP_T>::value,
    "Cannot use with non-engine component!");
  static_assert(std::is_same<engine_component_base, COMP_T>::value == false,
    "Cannot get base component!");

  auto & container = p_engine_components[COMP_T::type_id.value()];
  auto find_it = std::find(container.begin(), container.end(), comp);
  if(find_it != container.end())
  {
    std::swap(*find_it, container.back());
    container.pop_back();
  }
  else
  {
    LE_FATAL_ERROR("Attempting to unregister component that is not registered!");
  }
}

/*!
 * \brief For internal use only by entity, should not be manually called.
 * \todo Make private or refactor in some way?
 */
template<typename COMP_T>
void
space::register_logic_component(COMP_T * comp)
{
  static_assert(std::is_base_of<logic_component_base, COMP_T>::value,
    "Cannot use with non-logic component!");
  static_assert(std::is_same<logic_component_base, COMP_T>::value == false,
    "Cannot create base component!");

  // Add to container of all logic components as well as the container for this type
  p_logic_components[logic_component_base::type_id.value()].emplace_back(comp);
  p_logic_components[COMP_T::type_id.value()].emplace_back(comp);
}

/*!container
 * \brief For internal use only by entity, should not be manually called.
 * \note Should consider all iterators to logic components obtained from this space to be
 *   invalidated when called.
 * \todo Make private or refactor in some way?
 */
template<typename COMP_T>
void
space::unregister_logic_component(COMP_T * comp)
{
  static_assert(std::is_base_of<logic_component_base, COMP_T>::value,
    "Cannot use with non-logic component!");
  static_assert(std::is_same<logic_component_base, COMP_T>::value == false,
    "Cannot create base component!");

  auto unregister_logic_component_type = [&](
    COMP_T * comp,
    unique_id<logic_component_base>::value_type type_id)
  {
    auto & container = p_logic_components[type_id];
    auto find_it = std::find(container.begin(), container.end(), comp);
    if(find_it != container.end())
    {
      std::swap(*find_it, container.back());
      container.pop_back();
    }
    else
    {
      LE_FATAL_ERROR("Attempting to unregister component that is not registered!");
    }
  };

  unregister_logic_component_type(COMP_T::type_id.value());
  unregister_logic_component_type(logic_component_base::type_id.value());
}

} // namespace LE
