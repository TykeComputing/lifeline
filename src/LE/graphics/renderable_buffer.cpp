/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "renderable_buffer.h"

namespace LE
{

void renderable_array_buffer::bind() const
{
  vertex_array::bind(p_VAO);
}

void renderable_array_buffer::unbind() const
{
  vertex_array::unbind();
}

GLsizei renderable_array_buffer::get_num_verts() const
{
  return p_num_verts;
}

void renderable_array_buffer::draw(
  GLenum prim_mode, GLint starting_vertex, GLsizei vertex_count)
{
  vertex_buffer::draw_arrays(
    prim_mode, starting_vertex, vertex_count);
}

void renderable_element_buffer::bind() const
{
  vertex_array::bind(p_VAO);
}

void renderable_element_buffer::unbind() const
{
  vertex_array::unbind();
}

GLsizei renderable_element_buffer::get_num_verts() const
{
  return p_num_verts;
}

void renderable_element_buffer::draw(
  GLenum prim_mode, GLsizei starting_index, GLsizei index_count)
  {
    LE::vertex_buffer::draw_elements(
      prim_mode,
      index_count,
      GL_UNSIGNED_INT,
      starting_index * sizeof(GLuint));
  }

} // namespace LE
