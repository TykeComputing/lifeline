/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_GRAPHICS_RENDERABLE_BUFFER_H
#define LE_GRAPHICS_RENDERABLE_BUFFER_H

#include <LE/graphics/vertex_array.h>
#include <LE/graphics/vertex_buffer.h>

namespace LE
{

class renderable_array_buffer
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

class renderable_element_buffer
{
public:
  void bind() const;
  void unbind() const;

  template<typename VERTEX_T>
  void set_data(
    VERTEX_T const* verts,
    size_t num_verts,
    GLuint const* indices,
    size_t num_indices,
    GLenum usage);

  GLsizei get_num_verts() const;
  GLsizei get_num_indices() const;

private:
  vertex_array p_VAO;
  vertex_buffer p_VBO;
  vertex_buffer p_IBO;
  GLsizei p_num_verts = 0;
  GLsizei p_num_indices = 0;
};

} // namespace LE

#include "renderable_buffer.hpp"

#endif // LE_GRAPHICS_RENDERABLE_BUFFER_H
