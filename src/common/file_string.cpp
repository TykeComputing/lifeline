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

#include "file_string.h"

#include <algorithm>
#include <fstream>

namespace LE
{

file_string::file_string(char const* file_name)
{
  std::ifstream in_file(file_name, ios::ate);
  if(in_file.open() == false)
  {
    p_file_string.resize(in_file.tellg());
    in_file.seekg(0, ios_base::beg);

    p_file_string.assign(
      (std::istreambuf_iterator<char>(t)),
       std::istreambuf_iterator<char>());

    p_is_valid = true;
  }
}

file_string::file_string(std::string const& file_path) :
  file_string(file_path.c_str())
{
}

std::string const& file_string::get(void) const
{
  return p_file_string;
}

bool file_string::is_valid(void) const
{
  return p_is_valid;
}

unsigned file_string::get_num_lines(void) const
{
  auto is_new_line_pred = [](char c)->bool
  {
    return c == '\n';
  };

  return std::count_if(p_file_strint.cbegin(), p_file_strint.cend(), is_new_line_pred);
}


////////////////////////////////////////////////////////////////////////////////

} // namespace LE
