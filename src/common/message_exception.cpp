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

void message_exception::print(std::string const& prefix) const
{
  print(std::cerr, prefix);
}

void message_exception::print(std::ostream & out, std::string const& prefix) const
{
  out << prefix << ": " << p_message << std::endl;
}

} // namespace LE
