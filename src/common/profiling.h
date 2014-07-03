/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_PROFILING_H
#define LE_COMMON_PROFILING_H

#include <common/timer.h>

namespace LE
{

// fwd-decl
class profiling_records;

template<typename TIMER_T>
class profiling_point
{
public:
  profiling_point(profiling_records & records, std::string const& name);
  ~profiling_point();

private:
  std::string p_name;
  profiling_records & p_records;
  TIMER_T p_timer;
};

} // namespace LE

#include "profiling.hpp"

#endif // LE_COMMON_PROFILING_H
