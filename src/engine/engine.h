/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_ENGINE_H
#define LE_ENGINE_ENGINE_H

#include <common/profiling_records.h>

#include <engine/graphics_context.h>
#include <engine/OS_interface.h>
#include <engine/space.h>
#include <engine/window.h>

namespace LE
{

class engine
{
public:
  engine();

  void run();

  window const& get_window() const;

  void set_is_running(bool val);

private:
  OS_interface p_os_interface;
  window p_window;
  graphics_context p_graphics_context;
  space p_space;

  bool p_is_running = true;
};

} // namespace LE

#endif // LE_ENGINE_ENGINE_H
