/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_GRAPHICS_VERTEX_H
#define LE_GRAPHICS_VERTEX_H

#include <LE/common/macros.h>

#include <LE/math/vec.h>

namespace LE
{

LE_ENUM_3(vertex_attrib_type, position, texcoord, color)

namespace vertex
{

struct pos2
{
  pos2(vec2 const& position);

  static void specify_vertex_attributes();

  vec2 position;
};

struct pos2_tex2
{
  pos2_tex2(vec2 const& position, vec2 const& texcoord);

  static void specify_vertex_attributes();

  vec2 position;
  vec2 texcoord;
};

struct pos2_col4
{
  pos2_col4(vec2 const& position, vec4 const& color);

  static void specify_vertex_attributes();

  vec2 position;
  vec4 color;
};

}

} // namespace LE

#endif // LE_GRAPHICS_VERTEX_H
