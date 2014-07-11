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
#include <common/profiling.h>
#include <common/timer.h>

// TODO - Remove once all game logic is moved from hack to logic components
#include <game/game_hack.h>
#include <common/resource_exception.h>

namespace LE
{

engine::engine() :
  p_os_interface(),
  p_window(),
  p_graphics_context(p_window),
  p_space(*this)
{
  log_status(log_scope::ENGINE, "Base Directory: {}", p_os_interface.get_base_dir());
  //log_status(log_scope::ENGINE, "Preferred Directory: {}") << p_os_interface.get_preferred_dir();

  p_graphics_sys.update_render_target_size(p_window.get_size());
}

void engine::run()
{
  try
  {
    auto * game_hack_ent = p_space.create_entity("game_hack");
    auto * game_hack = game_hack_ent->create_component<game_hack_scene_component>();
    game_hack->initialize();


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
      p_profiling_records.start_new_record_entry();
      high_resolution_profiling_point pp(p_profiling_records, "total_frame");

      // Cap maximum number of iterations per frame. If there is a massive spike
      //   in frame time for any reason this will prevent the game from completely
      //   stalling while trying to update too many times.
      current_dt = std::min(current_dt, max_iterations_per_frame * update_dt);

      while(current_dt > update_dt)
      {
        p_os_interface.update();

        step(update_dt);

        current_dt -= update_dt;
      }

      render_frame();

      // Add the new dt to any leftover dt from updating.
      current_dt += frame_timer.poll();
      frame_timer.reset();
    }
  }
  catch(resource_exception const& e)
  {
    log_error(log_scope::ENGINE, "{}", e.what());
    LE_FATAL_ERROR("ERROR");
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

profiling_records &engine::get_profiling_records()
{
  return p_profiling_records;
}

profiling_records const& engine::get_profiling_records() const
{
  return p_profiling_records;
}

void engine::step(float dt)
{
  high_resolution_profiling_point pp(p_profiling_records, "update");

  try
  {
    // TODO - Iterate over all spaces

    // We only want to render debug drawing from most recent update.
    p_space.clear_ddraw();

    p_logic_sys.update(p_space, dt);
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
}

void engine::render_frame()
{
  {
    high_resolution_profiling_point pp(p_profiling_records, "graphics_system");
    p_graphics_sys.render(p_space);
  }

  {
    high_resolution_profiling_point pp(p_profiling_records, "buffer_swap");
    p_window.update();
  }
}

} // namespace LE
