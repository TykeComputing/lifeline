/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_ENTITY_H
#define LE_ENGINE_ENTITY_H

#include <memory>
#include <unordered_map>

#include <common/fatal_error.h>
#include <common/macros.h>
#include <common/unique_id.h>

#include <engine/component_base.h>

namespace LE
{

class entity
{
public:
  LE_NON_COPYABLE(entity)

  explicit entity(std::string const& name);

  template<typename COMP_T>
  COMP_T const*
  get_component() const
  {
    auto find_it = p_components.find(COMP_T::type_id);
    if(find_it == p_components.end())
    {
      return nullptr;
    }
    else
    {
      return static_cast<COMP_T const*>(find_it->second.get());
    }
  }

  template<typename COMP_T>
  COMP_T *
  get_component()
  {
    return const_cast<COMP_T *>(
      static_cast<entity const&>(*this).get_component<COMP_T>());
  }

  template<typename COMP_T, typename... ARG_TS>
  COMP_T *
  create_component(ARG_TS &&... args)
  {
    auto new_comp_it = p_components.emplace(
      std::make_pair(
        COMP_T::type_id,
        std::unique_ptr<COMP_T>{ new COMP_T{std::forward<ARG_TS>(args)...} } ));

    if(new_comp_it.second)
    {
      return static_cast<COMP_T *>(new_comp_it.first->second.get());
    }
    else
    {
      LE_FATAL_ERROR("Unable to add component!");
      return nullptr;
    }
  }

  void kill();

  unique_id<entity> const& get_id() { return p_id; }
  std::string const& get_name() { return p_name; }
  bool is_alive() const { return p_is_alive; }

private:
  std::unordered_map<unique_id<component_base>, std::unique_ptr<component_base>> p_components;

  std::string p_name = "unnamed";
  unique_id<entity> const p_id;

  bool p_is_alive = true;
};

} // namespace LE

#endif // LE_ENGINE_ENTITY_H
