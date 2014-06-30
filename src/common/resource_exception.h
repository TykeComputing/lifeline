/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_RESOURCE_EXCEPTION_H
#define LE_COMMON_RESOURCE_EXCEPTION_H

#include <common/message_exception.h>

namespace LE
{

class resource_exception : public message_exception
{
public:
  resource_exception();
  resource_exception(char const* message);
  resource_exception(std::string const& message);

private:
};

} // namespace LE

#endif // LE_COMMON_RESOURCE_EXCEPTION_H
