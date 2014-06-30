/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "shader_program.h"

#include <utility>

#include <common/fatal_error.h>
#include <common/logging.h>
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

    // If OpenGL implementation provides newline(s), get rid of it/them
    if(link_log.size() >= 2)
    {
      // Skip null terminator
      int newline_it = link_log_length - 2;
      while( (newline_it >= 0) && (link_log[newline_it] == '\n') )
      {
       link_log[newline_it] = '\0';
        --newline_it;
      }
    }

    log_error(log_scope::GRAPHICS, "GLSL SHADER LINKER ERRORS");
    log_error_no_prefix(log_line_seperator);
    log_error_no_prefix("== SHADER NAMES =======");
    for(auto const& shader_it : shaders)
    {
      log_error_no_prefix("{}") << shader_it->get_file_name().c_str();
    }
    log_error_no_prefix("=== ERROR LOG ===========");
    log_error_no_prefix("{}") << link_log.data();
    log_error_no_prefix(log_line_seperator);

    // cleanup from failure
    glDeleteProgram(p_raw_name);

    LE_FATAL_ERROR_IF_GL_ERROR();

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

    LE_FATAL_ERROR_IF_GL_ERROR();
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
      log_status("Uniform named \"{}\" not found!") << uniform_name;
    }

    return uniform_index;
  }
}

void shader_program::use(shader_program & sp)
{
  glUseProgram(sp.p_raw_name);
}

void shader_program::use_default()
{
  glUseProgram(0);
}

} // namespace LE
