/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_RESOURCE_H
#define LE_COMMON_RESOURCE_H

#include <string>
#include <stab.h>

namespace LE
{

template<typename raw_resource_t>
class resource
{
public:
  // Hands ownership of a resource over to this.
  resource(raw_resource_t * new_resource);

private:
  raw_resource_t * raw_resource;
};

} // namespace LE

#endif // LE_COMMON_RESOURCE_H
