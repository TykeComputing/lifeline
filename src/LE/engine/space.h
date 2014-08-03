/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_SPACE_H
#define LE_ENGINE_SPACE_H

#include <memory>
#include <unordered_map>
#include <vector>

#include <LE/common/unique_id.h>
#include <LE/engine/component_base.h>
#include <LE/engine/engine_component_base.h>
#include <LE/engine/entity.h>
#include <LE/engine/logic_component_base.h>
#include <LE/graphics/debug_draw_manager.h>

namespace LE
{

class engine;

class space
{
public:
  // Allows only entity to register components
  class component_registrar
  {
  private:
    static void register_engine_component(
      space * s,
      unique_id<engine_component_base>::value_type type_id,
      engine_component_base * comp);

    static void unregister_engine_component(
      space * s,
      unique_id<engine_component_base>::value_type type_id,
      engine_component_base * comp);

    static void register_logic_component(
      space * s,
      unique_id<logic_component_base>::value_type type_id,
      logic_component_base * comp);

    static void unregister_logic_component(
      space * s,
      unique_id<logic_component_base>::value_type type_id,
      logic_component_base * comp);

    friend class entity;
  };

  explicit space(std::string const& name);
  ~space();

  /**********************************************/
  /* Entity Management */
  /**********************************************/
  typedef std::unordered_map<
    unique_id<entity>::value_type,
    std::unique_ptr<entity> > entity_container;

  typedef std::vector<engine_component_base *> engine_component_container;
  typedef std::unordered_map<
    unique_id<engine_component_base>::value_type,
    engine_component_container> engine_component_type_container;
  typedef std::vector<logic_component_base *> logic_component_container;
  typedef std::unordered_map<
    unique_id<logic_component_container>::value_type,
    logic_component_container> logic_component_type_container;

  entity * create_entity(std::string const& name);

  entity * find_entity(std::string const& name);
  entity * find_entity(unique_id<entity> const& id);

  void kill_all();

  size_t entity_num() const { return p_entities.size(); }

  void remove_dead();

  /**********************************************/
  /* Component Tracking */
  /**********************************************/

  template<typename COMP_T>
  engine_component_container::iterator
  engine_component_begin();
  template<typename COMP_T>
  engine_component_container::iterator
  engine_component_end();

  template<typename COMP_T>
  logic_component_container::iterator
  logic_component_begin();
  template<typename COMP_T>
  logic_component_container::iterator
  logic_component_end();

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
  void p_set_owner(engine * new_owner);

  void p_register_engine_component(
    unique_id<engine_component_base>::value_type type_id,
    engine_component_base * comp);
  void p_unregister_engine_component(
    unique_id<engine_component_base>::value_type type_id,
    engine_component_base * comp);

  void p_register_logic_component(
    unique_id<logic_component_base>::value_type type_id,
    logic_component_base * comp);
  void p_unregister_logic_component(
    unique_id<logic_component_base>::value_type type_id,
    logic_component_base * comp);

  std::string p_name;
  entity_container p_entities;
  engine_component_type_container p_engine_components;
  logic_component_type_container p_logic_components;

  engine * p_owner = nullptr;

  bool p_is_active = true;

  friend class engine;
  friend class component_registrar;
};

} // namespace LE

#include "space.hpp"

#endif // LE_ENGINE_SPACE_H
