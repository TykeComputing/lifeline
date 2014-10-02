/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "fatal_construction_exception.h"

#include <iostream>

#include <LE/common/fatal_error.h>

namespace LE
{

fatal_construction_exception::fatal_construction_exception()
{
  LE_FATAL_ERROR("FATAL CONSTRUCTION EXCEPTION");
}

} // namespace LE
