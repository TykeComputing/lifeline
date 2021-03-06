/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_ENGINE_COMPONENT_BASE_H
#define LE_ENGINE_ENGINE_COMPONENT_BASE_H

#include <LE/engine/component_base.h>

namespace LE
{

/*!
 * \brief Used to store engine data for processing by engine systems.
 *
 * \note All components derived from this class must have a static public member `type_id` of
 *   type `unique_id<engine_component_base> const`.
 *
 * \warning Funtionality that requires access to any portion of the engine, such as access to
 *   owning entity, should **never** be used in the constructor (and should be avoided in
 *   destructor). Engine components should be self contained and not require other components -
 *   even transform - while constructing/destructing.
 */
class engine_component_base : public component_base
{
public:
  virtual ~engine_component_base() {}

  static unique_id<engine_component_base> const type_id;
private:
};

} // namespace LE

#endif // LE_ENGINE_ENGINE_COMPONENT_BASE_H
