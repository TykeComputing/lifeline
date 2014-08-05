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

/*!
 * \brief Creates a new space and queues it to be added to the engine.
 *    The new space will not be added until the next step.
 *
 * \note: Space will be drawn in the reverse order from which they are created (i.e. the oldest
 *   will be drawn last thus placing it ontop of everything else). TODO - Come up with better
 *   system than this (priority?)
 */
space * engine::create_space(std::string const& name)
{
  p_new_spaces.emplace_back(new space(name));
  log_status(log_scope::ENGINE,
    "Creating space named named \"{}\", {} spaces now in this engine.",
    name,
    p_spaces.size() + p_new_spaces.size());

  auto * new_space = p_new_spaces.back().get();
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

  for(auto const& curr_space : p_spaces)
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

  // Since spaces can add more spaces we wait until now to add spaces created last step.
  if(p_new_spaces.empty() == false)
  {
    //   Note that we want spaces created first to be last in the container, so we insert at the
    //   beginning and insert in reverse order.
    p_spaces.insert(
      p_spaces.begin(),
      std::make_move_iterator(p_new_spaces.rbegin()),
      std::make_move_iterator(p_new_spaces.rend()) );

    p_new_spaces.clear();
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
