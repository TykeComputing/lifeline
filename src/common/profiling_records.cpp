/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "profiling_records.h"

#include <algorithm>

#include <common/fatal_error.h>

namespace LE
{

void profiling_records::start_new_record_entry()
{
  ++num_record_entries;

  if(num_record_entries > max_num_record_entries)
  {
    // Get rid of the oldest record entry and add new record entry.
    for(auto & record : p_records)
    {
      record.second.pop_front();
    }
  }

  // Add new record
  for(auto & record : p_records)
  {
    record.second.push_back(0.0f);
  }
}

void profiling_records::add_to_record_entry(std::string const & label, float time)
{
  if(num_record_entries == 0)
  {
    return;
  }

  auto & record = p_records[label];
  if(record.size() < num_record_entries)
  {
    record.resize(num_record_entries, 0.0f);
  }

  record.back() += time;
}

size_t profiling_records::get_max_num_record_entries() const
{
  return max_num_record_entries;
}

void profiling_records::set_max_num_record_entries(size_t const& value)
{
  if(value < num_record_entries)
  {
    // If there are more records currently than the new maximum: shrink all existing records
    //   discarding the oldest entries.
    size_t num_to_discard = num_record_entries - value;
    for(auto & record : p_records)
    {
      for(unsigned i = 0; i < num_to_discard; ++i)
      {
        record.pop_front();
      }
    }

    num_record_entries = value;
  }

  max_num_record_entries = value;
}


} // namespace LE
