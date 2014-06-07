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

#include "engine.h"

#include <common/error.h>
#include <common/LE_printf.h>
#include <common/timer.h>

// TODO - Remove when done hacking
#include <game/game_hack.h>
#include <common/resource_exception.h>

namespace LE
{

engine::engine() :
  p_os_interface(),
  p_window(),
  p_graphics_context(p_window)
{
  LE_printf("Working Directory: %s\n", p_os_interface.get_working_dir().c_str());
}

void engine::run()
{
  

  std::unique_ptr<game_hack> game;
  try
  {
    game = std::make_unique<game_hack>(*this);
  }
  catch(LE::resource_exception const& e)
  {
    e.print("Game Construction");
    LE_ERROR("ERROR"); // Give time to look at error
    return;
  }

  p_is_running = true;
  while(p_is_running)
  {
    // Update
    // Temp hack to allow quiting
    set_is_running(p_os_interface.update());

    try
    {
      p_is_running = game->update();
    }
    catch(LE::resource_exception const& e)
    {
      e.print("Game");
      LE_ERROR("Uncaught resource exception!");
      return;
    }
    catch(LE::message_exception const& e)
    {
      e.print("Game");
      LE_ERROR("Uncaught message exception!");
      return;
    }

    p_window.update();
  }
}

void engine::set_is_running(bool val)
{
  p_is_running = val;
}

void engine::set_resource_dir(std::string const& val)
{
  if(val.empty())
  {
    LE_ERROR("Empty resource directory provided, ignoring.");
    return;
  }

  p_resource_dir = val;
  if(p_resource_dir.back() != '\\' && p_resource_dir.back() != '/')
  {
    p_resource_dir.append(1, '/');
  }

  LE_printf("Engine: Resource directory set to \"%s\"\n", p_resource_dir.c_str());
}

std::string const& engine::get_resource_dir() const
{
  return p_resource_dir;
}

} // namespace LE
