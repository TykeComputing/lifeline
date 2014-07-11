/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_RESOURCE_MANAGER_H
#define LE_COMMON_RESOURCE_MANAGER_H

#include <string>

namespace LE
{

class resource_manager
{
public:
  static void set_resource_dir(std::string const& val);
  static std::string const& get_resource_dir();

private:
  static std::string p_resource_dir;
};

} // namespace LE

#endif // LE_COMMON_RESOURCE_MANAGER_H
