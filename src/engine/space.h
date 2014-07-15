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

#include <graphics/debug_draw_manager.h>

namespace LE
{

class engine;

class space
{
public:
  space(std::string const& name);

  /**********************************************/
  /* Entity Management */
  /**********************************************/
  typedef std::unordered_map<
    unique_id<entity>::value_type,
    std::unique_ptr<entity> > entity_container;

  typedef std::vector<component_base *> component_type_container;

  entity * create_entity(std::string const& name);

  entity * find_entity(std::string const& name);
  entity * find_entity(unique_id<entity> const& id);

  // TODO - Remove, replace with ability to get containers of components of a given type
  //          for engine components and all logic components.
  entity_container::iterator entity_begin() { return p_entities.begin(); }
  entity_container::const_iterator entity_cbegin() const { return p_entities.cbegin(); }
  entity_container::iterator entity_end() { return p_entities.end(); }
  entity_container::const_iterator entity_cend() const { return p_entities.cend(); }

  size_t entity_num() const { return p_entities.size(); }

  void remove_dead();

  /**********************************************/
  /* Debug Drawing */
  /**********************************************/
  void clear_ddraw();

  /*
   * Each space has its own debug drawers to ensure that all debug drawing is properly layered.
   *   For example, this can be used to ensure that a performance visualze will not draw overtop
   *   a debug console (or visa verca as desired).
   */
  debug_draw_manager m_world_ddraw;
  debug_draw_manager m_hud_ddraw;

  /**********************************************/
  /* Utility */
  /**********************************************/
  std::string const& get_name() const;

  engine * get_owning_engine();
  engine const* get_owning_engine() const;

  void set_is_active(bool value);
  bool get_is_active() const;

private:
  void set_owner(engine * new_owner);

  std::string p_name;
  entity_container p_entities;

  engine * p_owner = nullptr;

  bool p_is_active = true;

  friend engine;
};

} // namespace LE

#endif // LE_ENGINE_SPACE_H
