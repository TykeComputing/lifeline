/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_PROFILING_H
#define LE_COMMON_PROFILING_H

#include <common/macros.h>
#include <common/timer.h>

namespace LE
{

// fwd-decl
class profiling_records;

template<typename TIMER_T = high_resolution_timer>
class profiling_point
{
public:
  LE_NON_COPYABLE(profiling_point);

  profiling_point(profiling_records & records, std::string const& name);
  ~profiling_point();

private:
  profiling_records & p_records;
  std::string p_name;
  TIMER_T p_timer;
};

} // namespace LE

#include "profiling.hpp"

#endif // LE_COMMON_PROFILING_H
