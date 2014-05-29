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

#ifndef LE_GRAPHICS_SHADER_PROGRAM_DEFINITION_H
#define LE_GRAPHICS_SHADER_PROGRAM_DEFINITION_H

#include <string>
#include <unordered_map>
#include <utility> // pair
#include <vector>

#include <GL/gl.h>

namespace LE
{

class shader_program_definition
{
public:
  shader_program_definition();
  //shader_program_definition(std::string const& spd_file_name);

  void add_shader_files(
      GLenum shader_type,
      std::string const& file_name);

private:
  typedef std::vector<std::string> shader_file_names;

  std::unordered_map<GLenum, shader_file_names> p_shader_sources;
};

} // namespace LE

#endif // LE_GRAPHICS_SHADER_PROGRAM_DEFINITION_H
