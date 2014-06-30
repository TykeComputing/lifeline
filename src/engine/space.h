/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
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
