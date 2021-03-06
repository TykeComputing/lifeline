/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "vertex_buffer.h"

#include <utility>

#include <LE/graphics/error_checking.h>

namespace LE
{

vertex_buffer::vertex_buffer()
{
  glGenBuffers(1, &p_raw_name);
}

vertex_buffer::~vertex_buffer()
{
  glDeleteBuffers(1, &p_raw_name);
}

void vertex_buffer::bind(GLenum target, vertex_buffer const& VBO)
{
  glBindBuffer(target, VBO.p_raw_name);
}

void vertex_buffer::unbind(GLenum target)
{
  glBindBuffer(target, 0);
}

void vertex_buffer::specify_vertex_attrtibute(
  GLuint attrib_index,
  GLint num_components, GLenum type, GLboolean normalized,
  GLsizei byte_stride, GLsizei byte_offset)
{
  glEnableVertexAttribArray(attrib_index);

  glVertexAttribPointer(
    attrib_index,
    num_components, type, normalized,
    byte_stride, reinterpret_cast<GLvoid*>(static_cast<uintptr_t>(byte_offset)) );
}

void vertex_buffer::set_data(GLenum target, GLsizeiptr size, GLvoid const* data, GLenum usage)
{
  glBufferData(target, size, data, usage);

  LE_FATAL_ERROR_IF_GL_ERROR();
}

void vertex_buffer::copy_data(
  vertex_buffer & destination, vertex_buffer const& source, GLsizeiptr size, GLenum usage)
{
  glBindBuffer(GL_COPY_READ_BUFFER, source.p_raw_name);
  glBindBuffer(GL_COPY_WRITE_BUFFER, destination.p_raw_name);

  // Allocate space for new data
  glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, usage);

  glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);

  glBindBuffer(GL_COPY_READ_BUFFER, 0);
  glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

  LE_FATAL_ERROR_IF_GL_ERROR();
}

void vertex_buffer::draw_arrays(
  GLenum prim_mode, GLint starting_vertex, GLsizei vertex_count)
{
  glDrawArrays(prim_mode, starting_vertex, vertex_count);
}

void vertex_buffer::draw_elements(
  GLenum prim_mode, GLsizei index_count, GLenum index_type, GLsizei vertex_byte_offset)
{
  // Last parameter "pointer" is used as an offset in modern OpenGL,
  //   is a pointer due to legacy OpenGL cruft.
  // See: http://stackoverflow.com/a/8283855/2507444
  glDrawElements(prim_mode, index_count, index_type,
    reinterpret_cast<GLvoid*>(static_cast<uintptr_t>(vertex_byte_offset)) );
}

} // namespace LE
