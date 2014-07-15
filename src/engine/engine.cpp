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

  p_graphics_sys.update_render_target_size(p_window.get_size());
}

void engine::run()
{
  try
  {
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

      // Cap maximum number of iterations per frame. If there is a massive spike in frame time
      //   for any reason this will prevent the game from completely stalling while trying to
      //   update too many times.
      current_dt = std::min(current_dt, max_iterations_per_frame * update_dt);

      while(current_dt > update_dt)
      {
        p_os_interface.update(*this, p_input_sys);

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
    log_error(log_scope::ENGINE, "{} - Uncaught resource exception, exiting!", e.what());
    LE_FATAL_ERROR("Uncaught resource exception!");
    return;
  }
  catch(message_exception const& e)
  {
    log_error(log_scope::ENGINE, "{} - Uncaught message exception, exiting!", e.what());
    LE_FATAL_ERROR("Uncaught message exception");
    return;
  }
}

space * engine::create_space(std::string const& name)
{
  if(find_space(name) != nullptr)
  {
    log_error(log_scope::ENGINE,
      "Attempting to create space named \"{0}\", but a space with the name \"{0}\" already exists.",
      name);
   }

  p_spaces.emplace_back(new space(name));
  log_status(log_scope::ENGINE,
    "Creating space named named \"{}\", {} spaces now in this engine.",
    name,
    p_spaces.size());

  auto * new_space = p_spaces.back().get();
  new_space->set_owner(this);

  return new_space;
}

space * engine::find_space(std::string const& name)
{
  for(auto const& curr_space : p_spaces)
  {
    if(curr_space->get_name() == name)
    {
      return curr_space.get();
    }
  }

  return nullptr;
}

window const& engine::get_window() const
{
  return p_window;
}

input_system const& engine::get_input_system() const
{
  return p_input_sys;
}

profiling_records &engine::get_profiling_records()
{
  return p_profiling_records;
}

profiling_records const& engine::get_profiling_records() const
{
  return p_profiling_records;
}

void engine::set_is_running(bool val)
{
  p_is_running = val;
}

void engine::step(float dt)
{
  high_resolution_profiling_point pp(p_profiling_records, "update");

  for(auto const& curr_space : p_spaces)
  {
    if(curr_space->get_is_active() == false)
    {
      continue;
    }

    curr_space->clear_ddraw();

    p_logic_sys.update(*curr_space, dt);

    curr_space->remove_dead();
  }
}

void engine::render_frame()
{
  {
    high_resolution_profiling_point pp(p_profiling_records, "graphics_system");

    p_graphics_sys.clear_render_target();

    for(auto const& curr_space : p_spaces)
    {
      if(curr_space->get_is_active() == false)
      {
        continue;
      }

      p_graphics_sys.render(*curr_space);
    }
  }

  {
    high_resolution_profiling_point pp(p_profiling_records, "buffer_swap");
    p_window.update();
  }
}

} // namespace LE
