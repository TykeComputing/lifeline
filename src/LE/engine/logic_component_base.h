/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_LOGIC_COMPONENT_BASE_H
#define LE_ENGINE_LOGIC_COMPONENT_BASE_H

#include <LE/engine/component_base.h>

namespace LE
{

/*!
 * \brief Used to execute any non-engine logic.
 *
 * \note All components derived from this class must have a static public member `type_id` of
 *   type `unique_id<logic_component_base> const`.
 *
 * \warning Funtionality that requires access to any portion of the engine, such as access to
 *   owning entity, should **never** be used in the constructor (and should be avoided in
 *   destructor). Instead initialize/teardown should be used.
 */
class logic_component_base : public component_base
{
public:
  virtual ~logic_component_base() {}

  /*!
   * \brief Called after creation, once component is fully linked into the engine.
   */
  virtual void initialize() {}

  /*!
   * \brief Called once per engine step.
   */
  virtual void update(float dt) { LE_UNUSED_VAR(dt); }

  /*!
   * \brief Called just before destruction.
   */
  virtual void teardown() {}

  static unique_id<logic_component_base> const type_id;
private:
};

} // namespace LE

#endif // LE_ENGINE_LOGIC_COMPONENT_BASE_H
