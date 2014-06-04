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

#ifndef LE_ENGINE_ENGINE_H
#define LE_ENGINE_ENGINE_H

#include "OS_interface.h"
#include "window.h"
#include "graphics_context.h"

namespace LE
{

class engine
{
public:
  engine();

  void run();

  void set_is_running(bool val);
  
  // TODO - Move to more appropriate place once there is one
  void set_resource_dir(std::string const& val);
  std::string const& get_resource_dir() const;

private:
  OS_interface p_os_interface;
  window p_window;
  graphics_context p_graphics_context;

  bool p_is_running = true;

  // TODO - Move to more appropriate place once there is one
  std::string p_resource_dir = "resources/";
};

} // namespace LE

#endif // LE_ENGINE_ENGINE_H
