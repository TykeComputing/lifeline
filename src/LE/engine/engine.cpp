/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "engine.h"

#include <algorithm>
#include <thread>

#include <LE/common/fatal_error.h>
#include <LE/common/logging.h>
#include <LE/common/profiling.h>
#include <LE/common/timer.h>

// TODO - Remove once all game logic is moved from hack to logic components
#include <LE/common/resource_exception.h>

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
      if(p_is_paused == false)
      {
        p_profiling_records.start_new_record_entry();
      }

      high_resolution_profiling_point pp(p_profiling_records, "total_frame");

      // Cap maximum number of iterations per frame. If there is a massive spike in frame time
      //   for any reason this will prevent the game from completely stalling while trying to
      //   update too many times.
      current_dt = std::min(current_dt, max_iterations_per_frame * update_dt);
      while(current_dt > update_dt)
      {
        p_os_interface.update(*this, p_input_sys);

        // Since this pauses absolutely everything except rendering, it need to be done in the
        //   engine itself.
        if(p_input_sys.is_key_released(SDLK_PAUSE))
        {
          p_is_paused = !p_is_paused;
        }

        if(p_is_paused == false)
        {
          step(update_dt);
        }

        current_dt -= update_dt;
      }

      render_frame();

      // Add the new dt to any leftover dt from updating.
      current_dt += frame_timer.poll();
      frame_timer.reset();
    }
  }
  catch(resource_exception const&)
  {
    log_error(log_scope::ENGINE, "Uncaught resource exception!");
    LE_FATAL_ERROR("Uncaught resource exception!");
  }

  log_status(log_scope::ENGINE, "Engine shutting down.");
}

space * engine::create_space(std::string const& name)
{
  // Insert new spaces at the front to ensure oldest spaces are drawn last.
  p_spaces.emplace(p_spaces.begin(), new space(name));
  log_status(log_scope::ENGINE,
    "Creating space named named \"{}\", {} spaces now in this engine.",
    name,
    p_spaces.size());

  auto * new_space = p_spaces.front().get();
  new_space->p_set_owner(this);

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

graphics_system const& engine::get_graphics_system() const
{
  return p_graphics_sys;
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

void engine::remove_dead_spaces()
{
  for(auto it = p_spaces.begin(); it != p_spaces.end();)
  {
    if((*it)->get_is_alive() == false)
    {
      log_status(log_scope::ENGINE,
        "Removing dead space named \"{}\", {} spaces now exist.",
          (*it)->get_name(),
          p_spaces.size() - 1); // don't count space being removed

      // Order of spaces DOES matter, cannot swap with back/pop_back
      it = p_spaces.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

void engine::step(float dt)
{
  high_resolution_profiling_point pp(p_profiling_records, "update");

  // Since spaces can add more spaces (through logic components), we need to iterate over a temp
  //   container while updating.
  std::vector<space *> spaces_to_update;
  spaces_to_update.reserve(p_spaces.size());
  for(auto const& curr_space : p_spaces)
  {
    spaces_to_update.push_back(curr_space.get());
  }

  for(auto const& curr_space : spaces_to_update)
  {
    if(curr_space->get_is_active() == false)
    {
      continue;
    }

    curr_space->clear_ddraw();

    p_logic_sys.update(*curr_space, dt);

    curr_space->remove_dead_entities();
  }

  remove_dead_spaces();
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
