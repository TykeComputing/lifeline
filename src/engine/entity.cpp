/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "entity.h"

#include <engine/space.h>

namespace LE
{

entity::entity(std::string const& name) :
  p_name(name)
{
}


/**********************************************/
/* Lifespan */
/**********************************************/

void entity::kill()
{
  p_is_alive = false;
}

/**********************************************/
/* Utility*/
/**********************************************/

space const* entity::get_owning_space() const
{
  return p_owner;
}

space * entity::get_owning_space()
{
  return p_owner;
}

void entity::set_owner(space * new_owner)
{
  p_owner = new_owner;
}

} // namespace LE
