/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_ENGINE_H
#define LE_ENGINE_ENGINE_H

#include <memory>
#include <vector>

#include <common/profiling_records.h>

#include <engine/graphics_context.h>
#include <engine/graphics_system.h>
#include <engine/input_system.h>
#include <engine/logic_system.h>
#include <engine/OS_interface.h>
#include <engine/space.h>
#include <engine/TTF_system.h>
#include <engine/window.h>

namespace LE
{



class engine
{
public:
  engine();

  void run();

  /*
   * NOTE: Space names are required to be unique. If a non-unique name is provided, no space
   *   will be created and nullptr will be returned.
   *
   * NOTE: Space will be drawn in the reverse order from which they are created (i.e. the oldest
   *         will be drawn last thus placing it ontop of everything else). TODO - Come up with
   *         better system than this (priority?)
   */
  space * create_space(std::string const& name);
  space * find_space(std::string const& name);

  window const& get_window() const;

  input_system const& get_input_system() const;
  graphics_system const& get_graphics_system() const;

  profiling_records & get_profiling_records();
  profiling_records const& get_profiling_records() const;

  void set_is_running(bool val);

private:
  void step(float dt);
  void render_frame();

  // NOTE: Order of initialization matters here
  OS_interface p_os_interface;
  window p_window;
  graphics_context p_graphics_context;

  input_system p_input_sys;
  logic_system p_logic_sys;
  graphics_system p_graphics_sys;
  TTF_system p_sprite_text_sys; // TODO - merge or move into graphics system?

  std::vector<std::unique_ptr<space>> p_spaces;

  profiling_records p_profiling_records;

  bool p_is_running = true;
};

} // namespace LE

#endif // LE_ENGINE_ENGINE_H
