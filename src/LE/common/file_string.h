/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
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

  unsigned get_num_lines() const;

  bool is_valid() const;
  std::string const& get_file_name() const;
  std::string const& get_str() const;

private:
  std::string p_file_string;
  std::string p_file_name;
  bool p_is_valid = false;
};

} // namespace LE

#endif // LE_COMMON_FILE_STRING_H
