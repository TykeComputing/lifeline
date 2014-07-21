/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_FATAL_CONSTRUCTION_EXCEPTION_H
#define LE_COMMON_FATAL_CONSTRUCTION_EXCEPTION_H

#include <string>

#include <LE/common/message_exception.h>

namespace LE
{

class fatal_construction_exception : public message_exception
{
public:
  fatal_construction_exception();
  fatal_construction_exception(char const* message);
  fatal_construction_exception(std::string const& message);

private:
};

} // namespace LE

#endif // LE_COMMON_FATAL_CONSTRUCTION_EXCEPTION_H
