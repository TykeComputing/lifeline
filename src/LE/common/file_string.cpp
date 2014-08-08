/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "file_string.h"

#include <algorithm>
#include <fstream>

namespace LE
{

file_string::file_string(char const* file_name) :
  p_file_name(file_name)
{
  std::ifstream in_file(file_name, std::ios::ate);
  if(in_file.is_open())
  {
    p_file_string.resize(static_cast<std::string::size_type>(in_file.tellg()));
    in_file.seekg(0, std::ios_base::beg);

    p_file_string.assign(
      (std::istreambuf_iterator<char>(in_file)),
       std::istreambuf_iterator<char>());

    p_is_valid = true;
  }
}

file_string::file_string(std::string const& file_path) :
  file_string(file_path.c_str())
{
}

unsigned file_string::get_num_lines() const
{
  // num lines = num newlines + 1 (first line)
  return 1 + std::count_if(
    p_file_string.cbegin(),
    p_file_string.cend(),
    std::bind2nd(std::equal_to<char>(), '\n'));
}

bool file_string::is_valid() const
{
  return p_is_valid;
}

std::string const& file_string::get_file_name() const
{
  return p_file_name;
}

std::string const& file_string::get_str() const
{
  return p_file_string;
}

////////////////////////////////////////////////////////////////////////////////

} // namespace LE
