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

#include <string>
#include <vector>

#include <GL/gl.h>

#include <common/file_string.h>
#include <common/resource_exception.h>

namespace LE
{

struct shader
{
  shader(GLenum type, std::vector<std::string> shader_soure_file_names) :
    p_type(type)
  {
    size_t num_shader_sources = shader_soure_file_names.size();

    // Load shader sources into memory
    std::vector<file_string> shader_source_strings;
    shader_source_strings.reserve(num_shader_sources);
    for(auto const& file_name_it : shader_soure_file_names)
    {
      shader_source_strings.emplace_back(*file_name_it);
      if(shader_source_strings.back().is_valid() == false)
      {
        throw resource_exception("Unable to open shader file \"" + *file_name_it + "\!");
      }
    }

    p_raw_shader_name = glCreateShader(type);
    if(p_raw_shader_name == 0)
    {
      throw resource_exception("Unable to create shader, internal OpenGL error!");
    }

    // Get input in the form that OpenGL requires (an array of c strings)
    std::vector<char const*> shader_source_c_str_array;
    shader_source_c_str_array.reserve(num_shader_sources);
    for(auto const& shader_string_it : shader_source_strings)
    {
      shader_source_c_str_array.emplace_back( (*shader_string_it).get().c_str() );
    }

    glShaderSource(
      p_raw_shader_name,
      shader_source_c_str_array.size(), shader_source_c_str_array.data(), nullptr);

    glCompileShader(p_raw_shader_name);
  }

  ~shader()
  {
    glDeleteShader(p_raw_shader_name);
  }

private:
  GLuint p_raw_shader_name = 0;
  GLenum p_type = GL_NONE;

  friend class shader_program;
};

class shader_program
{
public:
  shader_program(shader_program_definition const& spd);
  ~shader_program();

  GLint get_unform_location(char const* attrib_name) const;

  static void use(shader_program & sp);
  // TODO - static set_uniform's for built in type (single and vector), and LE types (vec*, etc)

private:
  GLuint p_raw_program_name = 0;
};

} // namespace LE

#endif // LE_GRAPHICS_SHADER_PROGRAM_H
