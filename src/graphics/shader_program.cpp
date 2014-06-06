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

#include "shader_program.h"

#include <utility>

#include <common/error.h>
#include <common/LE_printf.h>
#include <common/resource_exception.h>

#include <graphics/error_checking.h>
#include <graphics/vertex.h> // vertex_attribute_type

namespace LE
{

shader_program::shader_program(std::vector<shader*> const& shaders)
{
  p_raw_name = glCreateProgram();

  for(auto const& shader_it : shaders)
  {
    glAttachShader(p_raw_name, shader_it->p_raw_name);
  }

  // Bind vertex attribs
  // Quick and dirty solution, no need currently for a generic solution
  for(GLuint i = vertex_attrib_type::e_start; i != vertex_attrib_type::e_end; ++i)
  {
    glBindAttribLocation(p_raw_name, i, vertex_attrib_type::c_str[i]);
  }

  glLinkProgram(p_raw_name);

  GLint program_link_status;
  glGetProgramiv(p_raw_name, GL_LINK_STATUS, &program_link_status);
  if(program_link_status == GL_FALSE)
  {
    GLint link_log_length;
    glGetProgramiv(p_raw_name, GL_INFO_LOG_LENGTH, &link_log_length);

    // Allocate buffer and get link errors
    std::vector<char> link_log;
    link_log.resize(link_log_length);
    glGetProgramInfoLog(p_raw_name, link_log_length, nullptr, link_log.data());

    // If OpenGL implementation provides newline, get rid of it
    if(link_log.empty() == false && link_log.back() == '\n')
    {
      link_log.back() = '\0';
    }

    LE_printf("-- GLSL SHADER LINKER ERRORS: ----------------------------------\n");
    LE_printf("== SHADER NAMES =======\n");
    for(auto const& shader_it : shaders)
    {
      LE_printf("%s\n", shader_it->get_file_name().c_str());
    }
    LE_printf("=== ERROR LOG ===========\n");
    LE_printf("%s\n", link_log.data());
    LE_printf("----------------------------------------------------------------\n");

    // cleanup from failure
    glDeleteProgram(p_raw_name);

    LE_ERRORIF_GL_ERROR();

    throw resource_exception("Shader linking failed.");
  }
  else
  {
    // Detatch shaders as they are no longer needed (OpenGL will not delete shaders still attached
    //   to a program).
    for(auto const& shader_it : shaders)
    {
      glDetachShader(p_raw_name, shader_it->p_raw_name);
    }

    LE_ERRORIF_GL_ERROR();
  }
}

shader_program::~shader_program()
{
  glDeleteProgram(p_raw_name);
}

GLint shader_program::get_unform_location(char const* uniform_name) const
{
  auto find_it = p_uniform_locations.find(uniform_name);
  if(find_it != p_uniform_locations.end())
  {
    // uniform index already known
    return find_it->second;
  }
  else
  {
    // uniform index not known yet, find it and store it (if it exists)
    GLint uniform_index = glGetUniformLocation(p_raw_name, uniform_name);
    p_uniform_locations.insert(std::make_pair(uniform_name, uniform_index));

    if(uniform_index == -1)
    {
      LE_printf("Uniform named \"%s\" not found!", uniform_name);
    }

    return uniform_index;
  }
}

void shader_program::use(shader_program & sp)
{
  glUseProgram(sp.p_raw_name);
}

} // namespace LE
