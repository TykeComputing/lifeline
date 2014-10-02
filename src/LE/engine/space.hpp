/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

namespace LE
{

/*!
 * \brief Gets an iterator to the beginning of a container containing all of a certain type of
 *   engine component.
 *
 * \tparam COMP_T - Which type of engine components to get the begin of. Must be a class derived
 *   from engine_component_base.
 */
template<typename COMP_T>
space::engine_component_container::iterator
space::engine_component_begin()
{
  static_assert(std::is_base_of<engine_component_base, COMP_T>::value,
    "Cannot use with non-engine component!");
  static_assert(std::is_same<engine_component_base, COMP_T>::value == false,
    "Cannot get base component!");

  return p_engine_components[COMP_T::type_id.value()].begin();
}

/*!
 * see \ref engine_component_begin. Gets end of range instead of begin.
 */
template<typename COMP_T>
space::engine_component_container::iterator
space::engine_component_end()
{
  static_assert(std::is_base_of<engine_component_base, COMP_T>::value,
    "Cannot use with non-engine component!");
  static_assert(std::is_same<engine_component_base, COMP_T>::value == false,
    "Cannot get base component!");

  return p_engine_components[COMP_T::type_id.value()].end();
}

/*!
 * \brief Gets an iterator to the beginning of a container containing all of a certain type of
 *   logic component.
 *
 * \tparam COMP_T - Which type of engine components to get the end of. Must be a class derived
 *   from logic_component_base OR logic_component_base. If logic_component_base, the returned
 *   range contains all logic components.
 */
template<typename COMP_T>
space::logic_component_container::iterator
space::logic_component_begin()
{
  static_assert(std::is_base_of<logic_component_base, COMP_T>::value,
    "Cannot use with non-logic component!");

  return p_logic_components[COMP_T::type_id.value()].begin();
}

/*!
 * see \ref logic_component_begin. Gets end of range instead of begin.
 */
template<typename COMP_T>
space::logic_component_container::iterator
space::logic_component_end()
{
  static_assert(std::is_base_of<logic_component_base, COMP_T>::value,
    "Cannot use with non-logic component!");

  return p_logic_components[COMP_T::type_id.value()].end();
}

}
