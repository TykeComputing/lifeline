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

  static std::string full_dir(std::string const& relative_resource_file_path)
  {
    return resource_manager::get_resource_dir() + relative_resource_file_path;
  }

  // Dummy function, does nothing but always allocate at the moment
  // TODO - Store loaded resources after loading once and use these when load is called a
  //          second time (i.e. actual resource management).
  template<typename RESOURCE_T>
  static RESOURCE_T * load(std::string const& relative_resource_file_path)
  {
    return new RESOURCE_T{ full_dir(relative_resource_file_path) };
  }

private:
  static std::string p_resource_dir;
};

} // namespace LE

#endif // LE_COMMON_RESOURCE_MANAGER_H
