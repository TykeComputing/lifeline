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

#ifndef LE_ENGINE_OS_INTERFACE_H
#define LE_ENGINE_OS_INTERFACE_H

#include <string>

#include "graphics_context.h"
#include "window.h"

namespace LE
{

// fwd-decl
class engine;

class OS_interface
{
public:
  OS_interface();
  ~OS_interface();

  std::string get_base_dir(void) const;
  std::string get_preferred_dir(void) const; // UNIMPL - TODO

  bool update();

private:
};

} // namespace LE

#endif // LE_ENGINE_OS_INTERFACE_H
