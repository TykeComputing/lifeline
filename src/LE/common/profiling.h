/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_PROFILING_H
#define LE_COMMON_PROFILING_H

#include <LE/common/macros.h>
#include <LE/common/timer.h>

namespace LE
{

// fwd-decl
class profiling_records;

template<typename TIMER_T>
class profiling_point
{
public:
  LE_NON_COPYABLE(profiling_point)

  profiling_point(profiling_records & records, std::string const& name);
  ~profiling_point();

private:
  profiling_records & p_records;
  std::string p_name;
  TIMER_T p_timer;
};

typedef profiling_point<high_resolution_timer> high_resolution_profiling_point;
typedef profiling_point<steady_timer> steady_profiling_point;

} // namespace LE

#include "profiling.hpp"

#endif // LE_COMMON_PROFILING_H
