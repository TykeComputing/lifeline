/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_GRAPHICS_VERTEX_ARRAY_H
#define LE_GRAPHICS_VERTEX_ARRAY_H

#include <GL/glew.h>

#include <LE/common/macros.h>

namespace LE
{

class vertex_array
{
public:
  LE_NON_COPYABLE(vertex_array)

  vertex_array();
  ~vertex_array();

  static void bind(vertex_array const& VAO);
  static void unbind();

private:
  GLuint p_raw_name = 0;
};

} // namespace LE

#endif // LE_GRAPHICS_VERTEX_ARRAY_H
