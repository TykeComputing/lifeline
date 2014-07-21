/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "resource_manager.h"

#include <LE/common/fatal_error.h>
#include <LE/common/logging.h>

namespace LE
{

std::string resource_manager::p_resource_dir = "resources/";

void resource_manager::set_resource_dir(std::string const& val)
{
  if(val.empty())
  {
    LE_FATAL_ERROR("Empty resource directory provided, ignoring.");
    return;
  }

  p_resource_dir = val;
  if(p_resource_dir.back() != '\\' && p_resource_dir.back() != '/')
  {
    p_resource_dir.append(1, '/');
  }

  log_status(log_scope::ENGINE, "Resource directory set to \"{}\"",
    p_resource_dir.c_str());
}

std::string const& resource_manager::get_resource_dir()
{
  return p_resource_dir;
}

} // namespace LE
