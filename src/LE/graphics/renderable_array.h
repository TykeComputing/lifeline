/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_GRAPHICS_RENDERABLE_H
#define LE_GRAPHICS_RENDERABLE_H

#include <LE/graphics/vertex_array.h>
#include <LE/graphics/vertex_buffer.h>

namespace LE
{

class renderable_array
{
public:
  void bind() const;
  void unbind() const;

  template<typename VERTEX_T>
  void set_data(VERTEX_T const* verts, size_t num_verts, GLenum usage);

  GLsizei get_num_verts() const;

private:
  vertex_array p_VAO;
  vertex_buffer p_VBO;
  GLsizei p_num_verts = 0;
};

} // namespace LE

#include "renderable_array.hpp"

#endif // LE_GRAPHICS_RENDERABLE_H
