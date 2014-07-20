/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "entity.h"

#include <common/logging.h>

#include <engine/space.h>

namespace LE
{

entity::entity(std::string const& name) :
  p_name(name)
{
}

entity::~entity()
{
  if(p_parent)
  {
    p_parent->remove_child(this);
  }

  for(auto * child : p_children)
  {
    child->p_parent = nullptr;
  }

  for(auto const& curr_logic_comp : p_logic_components)
  {
    curr_logic_comp.second->teardown();
  }
}

/**********************************************/
/* Children */
/**********************************************/

void entity::add_child(entity * child)
{
  LE_FATAL_ERROR_IF(child == nullptr, "Attempting to add null child!");

  if(child->p_parent != nullptr)
  {
    LE_FATAL_ERROR("Attempting to child that already has a parent!");
    return;
  }

  p_children.push_back(child);
  child->p_parent = this;

  log_status(log_scope::ENGINE, "Adding child named \"{}\" to parent named \"{}\".",
    child->get_name(), get_name());
}

void entity::remove_child(entity * child)
{
  LE_FATAL_ERROR_IF(child == nullptr, "Attempting to remove null child!");

  if(child->p_parent != this)
  {
    // TODO - Remove child and attach to new parent?
    LE_FATAL_ERROR("Attempting to remove child that is not a child of this entity!");
    return;
  }

  auto find_it = std::find(p_children.begin(), p_children.end(), child);
  if(find_it != p_children.end())
  {
    p_children.erase(find_it);
    child->p_parent = nullptr;

    log_status(log_scope::ENGINE, "Removing child named \"{}\" from parent named \"{}\".",
      child->get_name(), get_name());
  }
  else
  {
    LE_FATAL_ERROR("Cannot find child to remove!");
  }
}

void entity::clear_children()
{
  for(auto * child : p_children)
  {
    child->p_parent = nullptr;
  }

  p_children.clear();
}

entity * entity::find_child(std::string const& name)
{
  return const_cast<entity *>(
    const_cast<entity const&>(*this).find_child(name) );
}

entity const* entity::find_child(std::string const& name) const
{
  for(auto * child : p_children)
  {
    if(child->get_name() == name)
    {
      return child;
    }
  }

  return nullptr;
}

/**********************************************/
/* Lifespan */
/**********************************************/

void entity::kill()
{
  p_is_alive = false;
  for(auto * child : p_children)
  {
    child->kill();
  }
}

/**********************************************/
/* Utility*/
/**********************************************/

space const* entity::get_owning_space() const
{
  return p_owner;
}

space * entity::get_owning_space()
{
  return p_owner;
}

void entity::set_owner(space * new_owner)
{
  p_owner = new_owner;
}

} // namespace LE
