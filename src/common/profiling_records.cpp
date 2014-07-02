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

void profiling_records::start_record_entry()
{
  LE_FATAL_ERROR_IF(curr_status == record_entry_started,
    "Every start_record_entry call must be matched with an end_record_entry call!");

  if(num_record_entries == max_num_record_entries)
  {
    // Get rid of the oldest records.
    for(auto & record : p_records)
    {
      record.second.pop_front();
    }
  }
  else
  {
    ++num_record_entries;
  }
}

void profiling_records::end_record_entry()
{
  for(auto & record : p_records)
  {
    if(record.second.size() != num_record_entries)
    {
      record.second.emplace_back(0.0f);
    }
  }
}

void profiling_records::add_to_record_entry(std::string const & label, float time)
{
  LE_FATAL_ERROR_IF(curr_status == record_entry_ended,
    "Attempting to add record entry outside of start_record_entry/end_record_entry pair.");

  if(num_record_entries == 0)
  {
    return;
  }

  auto record_find_it = p_records.find(label);
  if(record_find_it != p_records.end())
  {
    // A record container already exists with this name, use it.
    auto & record = record_find_it->second;


    if(record.size() == num_record_entries)
    {
      // The current record for this name already exists, add time to the existing record.
      records.back
    }
    else
    {
      // This name has no current record, create a new one.


      record.resize(num_record_entries, 0.0f);
    }
  }
  else
  {
    // Create a new time record container and fill it with dummy values so it will have the same
    //   number of entries as existing containers. This will mean that a given index will
    //   represent the same record for each time record container.

    auto record_insert_it = p_records.emplace(label);
    auto & record = record_insert_it.first->second;
    record.resize(num_record_entries, 0.0f);
  }
}

size_t profiling_records::get_max_num_record_entries() const
{
  return max_num_record_entries;
}

void profiling_records::set_max_num_record_entries(size_t const& value)
{
  if(value < max_num_record_entries)
  {
    num_record_entries = std::min(curr_record, value);
    // Shrink all existing record containers, discarding the oldest records.

    size_t num_to_discard = max_num_record_entries - value;
    for(auto & record : p_records)
    {
      if(record.size() != max_num_record_entries)
      {
        record.emplace_back(0.0f);
      }
    }
  }

  max_num_record_entries = value;
}


} // namespace LE
