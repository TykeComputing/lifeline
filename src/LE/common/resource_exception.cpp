/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "resource_exception.h"

#include <LE/common/fatal_error.h>

namespace LE
{

resource_exception::resource_exception()
{
  LE_FATAL_ERROR("RESOURCE EXCEPTION");
}

} // namespace LE
