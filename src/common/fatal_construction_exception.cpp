/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "fatal_construction_exception.h"

#include <iostream>

namespace LE
{

fatal_construction_exception::fatal_construction_exception()
{

}

fatal_construction_exception::fatal_construction_exception(char const* message) :
  message_exception(message)
{
}

fatal_construction_exception::fatal_construction_exception(std::string const& message) :
  message_exception(message)
{
}

} // namespace LE
