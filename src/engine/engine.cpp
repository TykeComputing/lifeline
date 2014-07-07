/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "engine.h"

#include <algorithm>
#include <thread>

#include <common/fatal_error.h>
#include <common/logging.h>
#include <common/timer.h>

// TODO - Remove once all game logic is moved from hack to logic components
#include <game/game_hack.h>
#include <common/resource_exception.h>

namespace LE
{

engine::engine() :
  p_os_interface(),
  p_window(),
  p_graphics_context(p_window)
{
  log_status(log_scope::ENGINE, "Base Directory: {}", p_os_interface.get_base_dir());
  //log_status(log_scope::ENGINE, "Preferred Directory: {}") << p_os_interface.get_preferred_dir();
}

void engine::run()
{
  try
  {
    std::unique_ptr<game_hack> game{new game_hack{*this, p_space}};


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
          p_is_running = game->update(p_space, update_dt);
        }
        catch(resource_exception const& e)
        {
          log_error(log_scope::ENGINE, "{}", e.what());
          LE_FATAL_ERROR("Uncaught resource exception!");
          return;
        }
        catch(message_exception const& e)
        {
          log_error(log_scope::ENGINE, "{}", e.what());
          LE_FATAL_ERROR("Uncaught message exception!");
          return;
        }

        p_space.remove_dead();

        current_dt -= update_dt;
      }

      game->draw(p_space);
      p_window.update();

      // Add the new dt to any leftover dt from updating.
      current_dt += frame_timer.poll();
      frame_timer.reset();
    }
  }
  catch(resource_exception const& e)
  {
    log_error(log_scope::ENGINE, "{}", e.what());
    LE_FATAL_ERROR("ERROR"); // Give time to look at error
  }
}

window const& engine::get_window() const
{
  return p_window;
}

void engine::set_is_running(bool val)
{
  p_is_running = val;
}

} // namespace LE
