/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_ENGINE_GRAPHICS_CONTEXT_H
#define LE_ENGINE_GRAPHICS_CONTEXT_H

#include "SDL.h"

namespace LE
{

// fwd-decl
class window;

class graphics_context
{
public:
  explicit graphics_context(window & target_window);
  ~graphics_context();

private:
  SDL_GLContext p_raw_context;
};

} // namespace LE

#endif // LE_ENGINE_GRAPHICS_CONTEXT_H
