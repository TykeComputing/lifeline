/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

namespace LE
{
/**********************************************/
/* General Component */
/**********************************************/

template<typename COMP_T, typename... ARG_TS>
typename std::enable_if<std::is_base_of<engine_component_base, COMP_T>::value,
  COMP_T *>::type
entity::create_component(ARG_TS &&... args)
{
  return create_engine_component<COMP_T, ARG_TS...>(std::forward<ARG_TS>(args)...);
}

template<typename COMP_T, typename... ARG_TS>
typename std::enable_if<std::is_base_of<logic_component_base, COMP_T>::value,
  COMP_T *>::type
entity::create_component(ARG_TS &&... args)
{
  return create_logic_component<COMP_T, ARG_TS...>(std::forward<ARG_TS>(args)...);
}

template<typename COMP_T>
typename std::enable_if<std::is_base_of<engine_component_base, COMP_T>::value,
  COMP_T *>::type
entity::get_component()
{
  return get_engine_component<COMP_T>();
}

template<typename COMP_T>
typename std::enable_if<std::is_base_of<logic_component_base, COMP_T>::value,
  COMP_T *>::type
entity::get_component()
{
  return get_logic_component<COMP_T>();
}

template<typename COMP_T>
typename std::enable_if<std::is_base_of<engine_component_base, COMP_T>::value,
  COMP_T const*>::type
entity::get_component() const
{
  return get_engine_component<COMP_T>();
}

template<typename COMP_T>
typename std::enable_if<std::is_base_of<logic_component_base, COMP_T>::value,
  COMP_T const*>::type
entity::get_component() const
{
  return get_logic_component<COMP_T>();
}

/**********************************************/
/* Engine Components */
/**********************************************/
// TODO: Improve method of storing/getting since number of types of engine componets will be
//         fixed.
template<typename COMP_T, typename... ARG_TS>
COMP_T *
entity::create_engine_component(ARG_TS &&... args)
{
  static_assert(std::is_base_of<engine_component_base, COMP_T>::value,
    "Cannot use with non-engine component!");
  static_assert(std::is_same<engine_component_base, COMP_T>::value == false,
    "Cannot create base component!");
  // TODO - Come up with a better method of specifying component types, this is ugly and
  //          potentially error-prone. Some safety-netting here.
  static_assert(
    std::is_same<engine_component_base, typename decltype(COMP_T::type_id)::scope>::value,
    "Mismatch between component type and type used for unique_id!");

  LE_FATAL_ERROR_IF(p_owner == nullptr, "Owner is null!");

  auto new_comp_it = p_engine_components.emplace(
    std::make_pair(
      COMP_T::type_id.value(),
      std::unique_ptr<COMP_T>{ new COMP_T{std::forward<ARG_TS>(args)...} } ));

  if(new_comp_it.second)
  {
    auto * new_comp = static_cast<COMP_T *>(new_comp_it.first->second.get());
    new_comp->set_owner(this);

    p_register_engine_component(COMP_T::type_id.value(), new_comp);

    return new_comp;
  }
  else
  {
    // Component already exists, duplicates not allowed.
    LE_FATAL_ERROR("Unable to add component!");
    return nullptr;
  }
}

template<typename COMP_T>
COMP_T const*
entity::get_engine_component() const
{
  static_assert(std::is_base_of<engine_component_base, COMP_T>::value,
    "Cannot use with non-engine component!");
  static_assert(std::is_same<engine_component_base, COMP_T>::value == false,
    "Cannot get base component!");

  auto find_it = p_engine_components.find(COMP_T::type_id.value());

  if(find_it != p_engine_components.end())
  {
    return static_cast<COMP_T const*>(find_it->second.get());
  }
  else
  {
    return nullptr;
  }
}

template<typename COMP_T>
COMP_T *
entity::get_engine_component()
{
  return const_cast<COMP_T *>(
    static_cast<entity const&>(*this).get_engine_component<COMP_T>() );
}

/**********************************************/
/* Logic Components */
/**********************************************/

template<typename COMP_T, typename... ARG_TS>
COMP_T *
entity::create_logic_component(ARG_TS &&... args)
{
  static_assert(std::is_base_of<logic_component_base, COMP_T>::value,
    "Cannot use with non-logic component!");
  static_assert(std::is_same<logic_component_base, COMP_T>::value == false,
    "Cannot create base component!");
  // TODO - Come up with a better method of specifying component types, this is ugly and
  //          potentially error-prone. Some safety-netting here.
  static_assert(
    std::is_same<logic_component_base, typename decltype(COMP_T::type_id)::scope>::value,
    "Mismatch between component type and type used for unique_id!");

  LE_FATAL_ERROR_IF(p_owner == nullptr, "Owner is null!");

  auto new_comp_it = p_logic_components.emplace(
    std::make_pair(
      COMP_T::type_id.value(),
      std::unique_ptr<COMP_T>{ new COMP_T{std::forward<ARG_TS>(args)...} } ));

  if(new_comp_it.second)
  {
    COMP_T * new_comp = static_cast<COMP_T *>(new_comp_it.first->second.get());
    new_comp->set_owner(this);
    p_register_logic_component(COMP_T::type_id.value(), new_comp);

    return new_comp;
  }
  else
  {
    // Component already exists, duplicates not allowed.
    LE_FATAL_ERROR("Unable to add component!");
    return nullptr;
  }
}

template<typename COMP_T>
void
entity::remove_logic_component()
{
  static_assert(std::is_base_of<logic_component_base, COMP_T>::value,
    "Cannot use with non-logic component!");
  static_assert(std::is_same<logic_component_base, COMP_T>::value == false,
    "Cannot remove base component!");

  auto find_it = p_logic_components.find(COMP_T::type_id.value());
  if(find_it != p_logic_components.end())
  {
    auto * comp = (*find_it).second;

    comp->tear_down();

    p_unregister_logic_component(COMP_T::type_id.value(), comp);

    p_logic_components.erase(find_it);
  }
}

template<typename COMP_T>
COMP_T const*
entity::get_logic_component() const
{
  static_assert(std::is_base_of<logic_component_base, COMP_T>::value,
    "Cannot use with non-logic component!");
  static_assert(std::is_same<logic_component_base, COMP_T>::value == false,
    "Cannot get base component!");

  auto find_it = p_logic_components.find(COMP_T::type_id.value());

  if(find_it != p_logic_components.end())
  {
    return static_cast<COMP_T const*>(find_it->second.get());
  }
  else
  {
    return nullptr;
  }
}

template<typename COMP_T>
COMP_T *
entity::get_logic_component()
{
  return const_cast<COMP_T *>(
    static_cast<entity const&>(*this).get_logic_component<COMP_T>() );
}

} // namespace LE
