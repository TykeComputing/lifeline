/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_GRAPHICS_VERTEX_BUFFER_H
#define LE_GRAPHICS_VERTEX_BUFFER_H

#include <GL/glew.h>

#include <LE/common/macros.h>

namespace LE
{

class vertex_buffer
{
public:
  LE_NON_COPYABLE(vertex_buffer)

  vertex_buffer();
  ~vertex_buffer();

  static void bind(GLenum target, vertex_buffer const& VBO);
  static void unbind(GLenum target);

  static void specify_vertex_attrtibute(
    GLuint attrib_index,
    GLint num_components, GLenum type, GLboolean normalized,
    GLsizei byte_stride, GLsizei byte_offset);

  static void set_data(GLenum target, GLsizeiptr size, GLvoid const* data, GLenum usage);
  static void copy_data(
    vertex_buffer & destination, vertex_buffer const& source, GLsizeiptr size, GLenum usage);

  static void draw_arrays(
    GLenum prim_mode, GLint starting_vertex, GLsizei vertex_count);
  static void draw_elements(
    GLenum prim_mode, GLsizei index_count, GLenum index_type, GLsizei vertex_byte_offset);

private:
  GLuint p_raw_name = 0;
};

} // namespace LE

#endif // LE_GRAPHICS_VERTEX_BUFFER_H
