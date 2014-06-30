/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_GRAPHICS_VERTEX_H
#define LE_GRAPHICS_VERTEX_H

#include <common/macros.h>

#include <math/vec.h>

namespace LE
{

LE_ENUM_3(vertex_attrib_type,
  position,
  texcoord,
  color)


struct vertex
{
  vertex(vec2 const& position, vec2 const& texcoord);

  static void specify_vertex_attributes();

  vec2 position;
  vec2 texcoord;
};

struct debug_shape_vertex
{
  debug_shape_vertex(vec2 const& position, vec4 const& color);

  static void specify_vertex_attributes();

  vec2 position;
  vec4 color;
};

} // namespace LE

#endif // LE_GRAPHICS_VERTEX_H
