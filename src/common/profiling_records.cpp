/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "profiling_records.h"

#include <algorithm>
#include <iostream>

#include <common/fatal_error.h>

namespace LE
{

//std::ostream & profiling_records::operator<<(std::ostream & os) const
//{
//  os << std::endl;
//  for(auto const& record : p_records)
//  {
//    os <<
//    for(auto const& record_entry : record)
//    {

//    }
//  }
//  os << std::endl;
//}

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

    num_record_entries = max_num_record_entries;
  }

  // Add new record entry to all existing records
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


profiling_records::time_record_container::const_iterator profiling_records::begin() const
{
  return p_records.begin();
}

profiling_records::time_record_container::const_iterator profiling_records::end() const
{
  return p_records.end();
}

profiling_records::time_record const*
profiling_records::get_record(std::string const& label) const
{
  auto record_find_it = p_records.find(label);
  if(record_find_it != p_records.end())
  {
    return &(record_find_it->second);
  }
  else
  {
    return nullptr;
  }
}

size_t profiling_records::get_max_num_record_entries() const
{
  return max_num_record_entries;
}

void profiling_records::set_max_num_record_entries(size_t const& value)
{
  if(value < num_record_entries)
  {
    // If there are more existing record entries than the new maximum, shrink all existing
    //   records discarding the oldest entries.
    size_t num_to_discard = num_record_entries - value;
    for(auto & record : p_records)
    {
      for(unsigned i = 0; i < num_to_discard; ++i)
      {
        record.second.pop_front();
      }
    }

    num_record_entries = value;
  }

  max_num_record_entries = value;
}

} // namespace LE
