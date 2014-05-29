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

#ifndef LE_COMMON_FILE_STRING_H
#define LE_COMMON_FILE_STRING_H

#include <string>

namespace LE
{

class file_string
{
public:
  file_string(char const* file_name);
  file_string(std::string const& file_name);

  char const* cbegin(void) const;
  char const* cend(void) const;

  unsigned get_num_lines(void) const;

  bool is_valid(void) const;
  std::string const& get(void) const;

private:
  std::string p_file_string;
  bool p_is_valid = false;
};

} // namespace LE

#endif // LE_COMMON_FILE_STRING_H
