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

#include "shader.h"

#include <utility>

#include <common/file_string.h>
#include <common/logging.h>

#include <common/resource_exception.h>

#include <graphics/error_checking.h>
#include <algorithm>

namespace LE
{

shader::shader(GLenum type, std::vector<std::string> const& shader_source_file_names) :
  p_type(type)
{
  if(shader_source_file_names.empty())
  {
    throw resource_exception("No shader sources specified!.");
  }

  // Since shader sources are copy pasted in order, it is safe to assume that the last
  //   name will be the most descriptive.
  p_file_name = shader_source_file_names.back();

  size_t num_shader_sources = shader_source_file_names.size();

  // Load shader sources into memory
  std::vector<file_string> shader_source_strings;
  shader_source_strings.reserve(num_shader_sources);
  for(auto const& file_name_it : shader_source_file_names)
  {
    shader_source_strings.emplace_back(file_name_it);
    if(shader_source_strings.back().is_valid() == false)
    {
      throw resource_exception("Unable to open shader file \"" + file_name_it + "\".");
    }
  }

  p_raw_name = glCreateShader(type);
  if(p_raw_name == 0)
  {
    throw resource_exception("Unable to create shader, internal OpenGL error.");
  }

  // Get input in the form that OpenGL requires (an array of c strings)
  std::vector<char const*> shader_source_c_str_array;
  shader_source_c_str_array.reserve(num_shader_sources);
  for(auto const& shader_string_it : shader_source_strings)
  {
    shader_source_c_str_array.emplace_back(shader_string_it.get_str().c_str());
  }

  glShaderSource(
    p_raw_name,
    shader_source_c_str_array.size(), shader_source_c_str_array.data(), nullptr);

  glCompileShader(p_raw_name);

  // Check for compilation failure
  GLint shader_compile_status;
  glGetShaderiv(p_raw_name, GL_COMPILE_STATUS, &shader_compile_status);
  if(shader_compile_status == GL_FALSE)
  {
    GLint compile_log_length;
    glGetShaderiv(p_raw_name, GL_INFO_LOG_LENGTH, &compile_log_length);

    // Allocate buffer and get compiler errors
    std::vector<char> compile_log;
    compile_log.resize(compile_log_length);
    glGetShaderInfoLog(p_raw_name, compile_log_length, nullptr, compile_log.data());

    // If OpenGL implementation provides newline(s), get rid of it/them
    if(compile_log.size() >= 2)
    {
      // Skip null terminator
      int newline_it = compile_log_length - 2;
      while( (newline_it >= 0) && (compile_log[newline_it] == '\n') )
      {
       compile_log[newline_it] = '\0';
        --newline_it;
      }
    }

    log_error(log_scope::graphics, "GLSL SHADER COMPILER ERRORS");
    log_error_no_prefix(log_line_seperator);
    log_error_no_prefix("== SHADER SOURCES =======");
    for(auto const& shader_source_it : shader_source_strings)
    {
      log_error_no_prefix("({:<3}) {}")
        << shader_source_it.get_num_lines()
        << shader_source_it.get_file_name().c_str();
    }
    log_error_no_prefix("=== ERROR LOG ===========");
    log_error_no_prefix("{}") << compile_log.data();
    log_error_no_prefix(log_line_seperator);

    // cleanup from failure
    glDeleteShader(p_raw_name);

    LE_FATAL_ERROR_IF_GL_ERROR();

    throw resource_exception("Shader compilation failed.");
  }

  LE_FATAL_ERROR_IF_GL_ERROR();
}

shader::~shader()
{
  glDeleteShader(p_raw_name);
}

std::string const& shader::get_file_name() const
{
  return p_file_name;
}

} // namespace LE
