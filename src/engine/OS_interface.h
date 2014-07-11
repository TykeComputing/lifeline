/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_OS_INTERFACE_H
#define LE_ENGINE_OS_INTERFACE_H

#include <string>

#include "graphics_context.h"
#include "window.h"

namespace LE
{

// fwd-decl
class engine;

class OS_interface
{
public:
  OS_interface();
  ~OS_interface();

  std::string get_base_dir() const;
  std::string get_preferred_dir() const; // UNIMPL - TODO

  void update();

private:
};

} // namespace LE

#endif // LE_ENGINE_OS_INTERFACE_H
