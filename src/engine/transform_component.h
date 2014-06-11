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

#ifndef LE_ENGINE_TRANSFORM_COMPONENT_H
#define LE_ENGINE_TRANSFORM_COMPONENT_H

#include <math/transform.h>
#include <math/vec.h>

#include <engine/component_base.h>

namespace LE
{

// TODO - Figure out how I'm going to handle transformation heirarchies and then decide on
//          final transform/transform_component design.
//      - Trying inheiritance based approch for now. I should evaluate if this is desirable
//          when implementing parenting.
class transform_component : public component_base, public transform
{
public:
  transform_component()
  {
    set_scale(0.1f, 0.1f);
  }

  static unique_id<component_base> const type_id;
};

} // namespace LE

#endif // LE_ENGINE_TRANSFORM_COMPONENT_H
