/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "message_exception.h"

#include <iostream>

namespace LE
{

message_exception::message_exception() :
  p_message("No message provided.")
{
}

message_exception::message_exception(char const* message) :
  p_message(message)
{
}

message_exception::message_exception(std::string const& message) :
  p_message(message)
{
}

std::string const& message_exception::what() const
{
  return p_message;
}

} // namespace LE
