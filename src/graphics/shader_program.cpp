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

#include <common/assert.h>

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



}

shader_program::~shader_program()
{

}

static void use(shader_program::shader_program & sp)
{
  glUseProgram(sp.p_raw_program_name);
}

} // namespace LE
