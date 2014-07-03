/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include <common/profiling_records.h>

namespace LE
{

template<typename TIMER_T>
profiling_point<TIMER_T>::profiling_point(profiling_records & records, std::string const& name) :
  p_records(records), p_name(name)
{
  p_timer.reset();
}

template<typename TIMER_T>
profiling_point<TIMER_T>::~profiling_point()
{
  p_records.add_to_record_entry(p_timer.poll);
}

} // namespace LE
