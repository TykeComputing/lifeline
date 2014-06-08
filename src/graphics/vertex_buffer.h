/*
************************************************************************************************
Copyright 2014 Peter Clark

This file is part of Lifeline Engine.

Lifeline Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Lifeline Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Lifeline Engine.  If not, see <http://www.gnu.org/licenses/>.
************************************************************************************************
*/

#ifndef LE_GRAPHICS_VERTEX_BUFFER_H
#define LE_GRAPHICS_VERTEX_BUFFER_H

#include <GL/glew.h>

#include <common/macros.h>

namespace LE
{

class vertex_buffer
{
public:
  LE_NON_COPYABLE(vertex_buffer)

  vertex_buffer();
  ~vertex_buffer();

  static void bind(GLenum target, vertex_buffer & VBO);
  static void unbind(GLenum target);

  static void specify_vertex_attrtibute(
    GLuint attrib_index,
    GLint num_components, GLenum type, GLboolean normalized,
    GLsizei byte_stride, GLsizei byte_offset);

  static void set_data(GLenum target, GLsizeiptr size, GLvoid const* data, GLenum usage);
  static void copy_data(
    vertex_buffer & destination, vertex_buffer const& source, GLsizeiptr size, GLenum usage);

  static void draw_arrays(
    GLenum mode, GLint vertex_offset, GLsizei vertex_count);
  static void draw_elements(
    GLenum mode, GLsizei index_count, GLenum index_type, GLsizei vertex_byte_offset);

private:
  GLuint p_raw_name = 0;
};

} // namespace LE

#endif // LE_GRAPHICS_VERTEX_BUFFER_H
