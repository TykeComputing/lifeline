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

#ifndef LE_ENGINE_ENTITY_H
#define LE_ENGINE_ENTITY_H

#include <memory>
#include <unordered_map>

#include <common/error.h>
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

  template<typename COMP_T>
  COMP_T *
  create_component()
  {
    auto new_comp_it = p_components.emplace(
      std::make_pair(COMP_T::type_id, std::unique_ptr<COMP_T>{new COMP_T}));

    if(new_comp_it.second)
    {
      return static_cast<COMP_T *>(new_comp_it.first->second.get());
    }
    else
    {
      LE_ERROR("Unable to add component!");
      return nullptr;
    }
  }

  unique_id<entity> const& get_id() { return p_id; }
  std::string const& get_name() { return p_name; }

private:
  std::unordered_map<unique_id<component_base>, std::unique_ptr<component_base>> p_components;

  std::string p_name = "unnamed";
  unique_id<entity> const p_id;
};

} // namespace LE

#endif // LE_ENGINE_ENTITY_H
