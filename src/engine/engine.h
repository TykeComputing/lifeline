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

  void set_is_running(bool val);

  // TODO - Move to more appropriate place once there is one
  void set_resource_dir(std::string const& val);
  std::string const& get_resource_dir() const;

private:
  OS_interface p_os_interface;
  window p_window;
  graphics_context p_graphics_context;

  bool p_is_running = true;

  // TODO - Move to more appropriate place once there is one (resource manager)
  std::string p_resource_dir = "resources/";

  space p_space;
};

} // namespace LE

#endif // LE_ENGINE_ENGINE_H
