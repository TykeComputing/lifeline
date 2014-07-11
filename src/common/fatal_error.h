/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_FATAL_ERROR_H
#define LE_COMMON_FATAL_ERROR_H

#include <string>

#include <SDL2/SDL.h>

#if defined __GNUC__
#include <sys/signal.h>
#define LE_HALT_PROGRAM() raise(SIGTRAP);
#elif defined _MSC_VER
#define LE_HALT_PROGRAM() __debugbreak();
#else
#define LE_HALT_PROGRAM()
#endif


#define LE_FATAL_ERROR(msg) \
{ \
  ::LE::internal::display_assert(__FILE__, __FUNCTION__, __LINE__, msg);\
  LE_HALT_PROGRAM(); \
}
#define LE_FATAL_ERROR_IF(cond, msg) { if(cond) { LE_FATAL_ERROR(msg); } }

namespace LE
{

namespace internal
{
  void display_assert(
    std::string const& file,
    std::string const& function,
    int line,
    char const* message);

  void display_assert(
    std::string const& file,
    std::string const& function,
    int line,
    std::string const& message);
}

}

#endif // LE_COMMON_FATAL_ERROR_H
