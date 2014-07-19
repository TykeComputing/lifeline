/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_ENTITY_H
#define LE_ENGINE_ENTITY_H

#include <memory>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include <common/fatal_error.h>
#include <common/macros.h>
#include <common/unique_id.h>

#include <engine/component_base.h>
#include <engine/engine_component_base.h>
#include <engine/logic_component_base.h>

namespace LE
{

// fwd-decls
class space;

class entity
{
public:
  LE_NON_COPYABLE(entity)

  explicit entity(std::string const& name);
  ~entity();

  /**********************************************/
  /* Children */
  /**********************************************/

  // Children are marked as killed when their parent is marked as killed.
  void add_child(entity * child);
  void remove_child(entity * child);
  void clear_children();

  // Detaches this entity from its parent (if it has one).
  void orphan();

  entity * find_child(std::string const& name);
  entity const* find_child(std::string const& name) const;

  /**********************************************/
  /* General Component */
  /**********************************************/

  template<typename COMP_T, typename... ARG_TS>
  typename std::enable_if<std::is_base_of<engine_component_base, COMP_T>::value,
    COMP_T *>::type
  create_component(ARG_TS &&... args);

  template<typename COMP_T, typename... ARG_TS>
  typename std::enable_if<std::is_base_of<logic_component_base, COMP_T>::value,
    COMP_T *>::type
  create_component(ARG_TS &&... args);

  template<typename COMP_T>
  typename std::enable_if<std::is_base_of<engine_component_base, COMP_T>::value,
    COMP_T *>::type
  get_component();

  template<typename COMP_T>
  typename std::enable_if<std::is_base_of<logic_component_base, COMP_T>::value,
    COMP_T *>::type
  get_component();

  template<typename COMP_T>
  typename std::enable_if<std::is_base_of<engine_component_base, COMP_T>::value,
    COMP_T const*>::type
  get_component() const;

  template<typename COMP_T>
  typename std::enable_if<std::is_base_of<logic_component_base, COMP_T>::value,
    COMP_T const*>::type
  get_component() const;

  /**********************************************/
  /* Engine Components */
  /**********************************************/
  // TODO: Improve method of storing/getting since number of types of engine componets will be
  //         fixed.
  template<typename COMP_T, typename... ARG_TS>
  COMP_T *
  create_engine_component(ARG_TS &&... args);

  template<typename COMP_T>
  COMP_T const*
  get_engine_component() const;

  template<typename COMP_T>
  COMP_T *
  get_engine_component();

  /**********************************************/
  /* Logic Components */
  /**********************************************/

  template<typename COMP_T, typename... ARG_TS>
  COMP_T *
  create_logic_component(ARG_TS &&... args);

  template<typename COMP_T>
  void
  remove_logic_component();

  template<typename COMP_T>
  COMP_T const*
  get_logic_component() const;

  template<typename COMP_T>
  COMP_T *
  get_logic_component();

  /////////////////////////////////////////////////
  // HACK HACK HACK
  // TODO - Make typedef private and remove functions
  typedef std::unordered_map<
    unique_id<logic_component_base>::value_type,
    std::unique_ptr<logic_component_base>> logic_component_container;

  logic_component_container::iterator logic_component_begin() { return p_logic_components.begin(); }
  logic_component_container::iterator logic_component_end() { return p_logic_components.end(); }
  /////////////////////////////////////////////////

  /**********************************************/
  /* Lifespan */
  /**********************************************/

  void kill();

  bool is_alive() const { return p_is_alive; }

  /**********************************************/
  /* Utility */
  /**********************************************/

  space const* get_owning_space() const;
  space * get_owning_space();

  unique_id<entity> const& get_id() { return p_id; }

  std::string const& get_name() { return p_name; }

private:
  void set_owner(space * new_owner);

  space * p_owner = nullptr;

  entity * p_parent = nullptr;
  std::vector<entity *> p_children;

  typedef std::unordered_map<
    unique_id<engine_component_base>::value_type,
    std::unique_ptr<component_base>> engine_component_container;

  engine_component_container p_engine_components;
  logic_component_container p_logic_components;

  std::string p_name = "unnamed";
  unique_id<entity> const p_id;

  bool p_is_alive = true;

  friend class space;
};

} // namespace LE

#include "entity.hpp"

#endif // LE_ENGINE_ENTITY_H
