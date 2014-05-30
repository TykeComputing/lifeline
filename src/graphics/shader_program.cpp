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

#include <common/error.h>
#include <common/LE_printf.h>
#include <common/resource_exception.h>

namespace LE
{

shader_program::shader_program(std::vector<shader> const& shaders)
{
  for(auto const& shader_it : shaders)
  {
    glAttachShader(p_raw_program_name, shader_it.p_raw_shader_name);
  }

  // TODO - Bind vertex attribs here

  glLinkProgram(p_raw_program_name);

  GLint program_link_status;
  glGetProgramiv(p_raw_program_name, GL_LINK_STATUS, &program_link_status);
  if(program_link_status == GL_FALSE)
  {
    GLint link_log_length;
    glGetProgramiv(p_raw_program_name, GL_INFO_LOG_LENGTH, &link_log_length);

    // Allocate buffer and get link errors
    std::vector<char> link_log;
    link_log.resize(link_log_length);
    glGetProgramInfoLog(p_raw_program_name, link_log_length, nullptr, link_log.data());

    // If OpenGL implementation provides newline, get rid of it
    if(link_log.empty() == false && link_log.back() == '\n')
    {
      link_log.back() = '\0';
    }

    LE_printf("-- GLSL SHADER LINKER ERRORS: --------------------------------\n");
    LE_printf("== SHADER NAMES =======");
    for(auto const& shader_it : shaders)
    {
      LE_printf("%s\n", shader_it.get_file_name().c_str());
    }
    LE_printf("=== ERROR LOG ===========\n");
    LE_printf("%s\n", link_log.data());
    LE_printf("----------------------------------------------------------------\n");

    // cleanup from failure
    glDeleteProgram(p_raw_program_name);

    throw resource_exception("Shader linking failed.");
  }
}

shader_program::~shader_program()
{
  glDeleteProgram(p_raw_program_name);
}

void shader_program::use(shader_program & sp)
{
  glUseProgram(sp.p_raw_program_name);
}

} // namespace LE
