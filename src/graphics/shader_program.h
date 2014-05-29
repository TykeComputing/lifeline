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

#ifndef LE_GRAPHICS_SHADER_PROGRAM_H
#define LE_GRAPHICS_SHADER_PROGRAM_H

#include <vector>

#include <GL/gl.h>

#include <common/file_string.h>
#include <common/resource_exception.h>

#include <graphics/shader.h>

namespace LE
{

class shader_program
{
public:
  shader_program(std::vector<shader> const& shaders);
  ~shader_program();

  GLint get_unform_location(char const* attrib_name) const;

  static void use(shader_program & sp);
  // TODO - static set_uniform's for built in type (single and vector), and LE types (vec*, etc)

private:
  GLuint p_raw_program_name = 0;
};

} // namespace LE

#endif // LE_GRAPHICS_SHADER_PROGRAM_H
