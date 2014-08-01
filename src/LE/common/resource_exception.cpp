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
  LE_FATAL_ERROR("NO MESSAGE");
}

resource_exception::resource_exception(char const* message) :
  message_exception(message)
{
  LE_FATAL_ERROR("{}", message);
}

resource_exception::resource_exception(std::string const& message) :
  message_exception(message)
{
  LE_FATAL_ERROR("{}", message.c_str());
}

} // namespace LE
