/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_GRAPHICS_DEBUG_DRAW_MANAGER_H
#define LE_GRAPHICS_DEBUG_DRAW_MANAGER_H

#include <LE/graphics/debug_drawer.h>

namespace LE
{

class debug_draw_manager
{
public:
  debug_line_drawer lines;
  debug_line_drawer dashed_lines;
  debug_point_drawer points;

  void clear();
  void draw() const;

private:
};

} // namespace LE

#endif // LE_GRAPHICS_DEBUG_DRAW_MANAGER_H
