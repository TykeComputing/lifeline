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

#ifndef LE_GRAPHICS_TEXTURE_H
#define LE_GRAPHICS_TEXTURE_H

#include <string>
#include <GL/glew.h>

namespace LE
{

// TODO - URGENT Refactor interface to follow conventions established by vertex_buffer.
class texture
{
public:
  texture(std::string const& texture_file_name);
  ~texture();

  static void set_active_texture_unit(GLuint unit_index);

  static void bind(GLenum target, texture const& tex);
  static void unbind(GLenum target);

private:
  GLuint p_raw_name = 0;
};

} // namespace LE

#endif // LE_GRAPHICS_TEXTURE_H
