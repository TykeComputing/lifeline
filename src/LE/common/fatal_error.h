/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_FATAL_ERROR_H
#define LE_COMMON_FATAL_ERROR_H

#include <string>

#include <SDL2/SDL.h>

#include <LE/common/cppformat.h>

#if defined __GNUC__
#include <sys/signal.h>
#define LE_HALT_PROGRAM() raise(SIGTRAP);
#elif defined _MSC_VER
#define LE_HALT_PROGRAM() __debugbreak();
#else
#define LE_HALT_PROGRAM()
#endif

/*!
 * \def LE_FATAL_ERROR(...)
 *
 * Displays an error pop up (if available). Takes a format string followed by a varaible
 *   number of parameters.
 */
#define LE_FATAL_ERROR(...) \
{ \
  ::LE::internal::display_assert(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__);\
  LE_HALT_PROGRAM(); \
}

/*!
 * \def LE_FATAL_ERROR_IF(cond, ...)
 *
 * If cond (condition) is true, calls \ref LE_FATAL_ERROR(...)
 */
#define LE_FATAL_ERROR_IF(cond, ...) \
{ \
  if(cond)\
  { \
    LE_FATAL_ERROR(__VA_ARGS__); \
  } \
}

namespace LE
{

namespace internal
{
  void display_assert(
    char const* file,
    char const* function,
    int line,
    char const* format,
    fmt::ArgList const& args);

  FMT_VARIADIC(void, display_assert, char const*,  char const*, int, char const*)
}

}

#endif // LE_COMMON_FATAL_ERROR_H
