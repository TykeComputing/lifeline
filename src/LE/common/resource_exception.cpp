/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "resource_exception.h"

namespace LE
{

resource_exception::resource_exception()
{

}

resource_exception::resource_exception(char const* message) :
  message_exception(message)
{
}

resource_exception::resource_exception(std::string const& message) :
  message_exception(message)
{
}

} // namespace LE
