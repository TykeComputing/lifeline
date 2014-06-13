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

#include <algorithm>

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
  LE_printf("Base Directory: %s\n", p_os_interface.get_base_dir().c_str());
  //LE_printf("Preferred Directory: %s\n", p_os_interface.get_preferred_dir().c_str());
}

void engine::run()
{
  try
  {
    std::unique_ptr<game_hack> game{new game_hack{*this}};


    // Credit for method of fixed time stepping:
    // http://ludobloom.com/tutorials/timestep.html
    // TODO - Test and improve.
    unsigned const max_frame_rate = 60;
    unsigned const min_frame_rate = 15;
    float const update_dt = 1.0f / max_frame_rate;
    float const max_iterations_per_frame = max_frame_rate / min_frame_rate;

    float current_dt = update_dt;
    high_resolution_timer frame_timer;
    frame_timer.start();

    p_is_running = true;
    while(p_is_running)
    {
      // Cap maximum number of iterations per frame. If there is a massive spike
      //   in frame time for any reason this will prevent the game from completely
      //   stalling while trying to update too many times.
      current_dt = std::min(current_dt, max_iterations_per_frame * update_dt);

      while(current_dt > update_dt)
      {
        // Temp hack to allow quiting
        set_is_running(p_os_interface.update());

        try
        {
          p_is_running = game->update(update_dt);
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

        current_dt -= update_dt;
      }

      game->draw();
      p_window.update();

      // Add the new dt to any leftover dt from updating.
      current_dt += frame_timer.poll();
      frame_timer.reset();
    }
  }
  catch(LE::resource_exception const& e)
  {
    e.print("Game Construction");
    LE_ERROR("ERROR"); // Give time to look at error
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
