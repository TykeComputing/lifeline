/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "debug_draw_manager.h"

namespace LE
{

void debug_draw_manager::clear()
{
  lines.clear();
  dashed_lines.clear();
  points.clear();
}

void debug_draw_manager::draw() const
{
  lines.draw();

  // Some graphics debugging tools do not support use of deprecated functions (such as NVIDIA
  //   NSight).
#ifndef LE_MODERN_OPENGL_ONLY
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(8, 0xAAAA);
#endif
  dashed_lines.draw();
#ifndef LE_MODERN_OPENGL_ONLY
  glDisable(GL_LINE_STIPPLE);
#endif

  points.draw();
}

} // namespace LE
