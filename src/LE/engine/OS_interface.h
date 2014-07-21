/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_OS_INTERFACE_H
#define LE_ENGINE_OS_INTERFACE_H

#include <string>

#include "graphics_context.h"
#include <LE/engine/input_system.h>

namespace LE
{

// TODO - Remove if messaging is implemented
// fwd-decl
class engine;

class OS_interface
{
public:
  OS_interface();
  ~OS_interface();

  // TODO - Remove engine parameter if messaging is implemented
  void update(engine & game_engine, input_system & input_sys);

  std::string get_base_dir() const;
  std::string get_preferred_dir() const; // UNIMPL - TODO

private:
};

} // namespace LE

#endif // LE_ENGINE_OS_INTERFACE_H
