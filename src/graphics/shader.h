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

#ifndef LE_GRAPHICS_SHADER_H
#define LE_GRAPHICS_SHADER_H

#include <string>
#include <vector>

#include <GL/glew.h>

namespace LE
{

class shader
{
public:
  shader(GLenum type, std::vector<std::string> const& shader_soure_file_names);
  ~shader();

  std::string const& get_file_name() const;

private:
  GLuint p_raw_name = 0;
  GLenum p_type = GL_NONE;
  std::string p_file_name;

  friend class shader_program;
};

} // namespace LE

#endif // LE_GRAPHICS_SHADER_H
