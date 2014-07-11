/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_ENGINE_H
#define LE_ENGINE_ENGINE_H

#include <common/profiling_records.h>

#include <engine/graphics_context.h>
#include <engine/graphics_system.h>
#include <engine/logic_system.h>
#include <engine/OS_interface.h>
#include <engine/space.h>
#include <engine/sprite_text_system.h>
#include <engine/window.h>

#include <game/game_hack.h>

namespace LE
{



class engine
{
public:
  engine();

  void run();

  window const& get_window() const;

  void set_is_running(bool val);

  profiling_records & get_profiling_records();

private:
  void step(float dt);
  void render_frame();

  OS_interface p_os_interface;
  window p_window;
  graphics_context p_graphics_context;

  logic_system p_logic_sys;
  graphics_system p_graphics_sys;
  sprite_text_system p_sprite_text_sys; // TODO - merge or move into graphics system?

  // TODO - Container of spaces
  space p_space;

  profiling_records p_profiling_records;

  bool p_is_running = true;
};

} // namespace LE

#endif // LE_ENGINE_ENGINE_H
