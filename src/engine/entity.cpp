/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "entity.h"

namespace LE
{

entity::entity(std::string const& name) :
  p_name(name)
{
}

void entity::kill()
{
  p_is_alive = false;
}

} // namespace LE
