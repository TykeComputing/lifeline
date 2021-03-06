/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "profiling_records.h"

#include <algorithm>
#include <iostream>

#include <LE/common/cppformat.h>
#include <LE/common/fatal_error.h>

namespace LE
{

void profiling_records::start_new_record_entry()
{
  ++p_num_record_entries;

  if(p_num_record_entries > p_max_num_record_entries)
  {
    // Get rid of the oldest record entry and add new record entry.
    for(auto & key_record_pair : p_records)
    {
      key_record_pair.second.pop_front();
    }

    p_num_record_entries = p_max_num_record_entries;
  }

  // Add new record entry to all existing records
  for(auto & key_record_pair : p_records)
  {
    key_record_pair.second.push_back(0.0f);
  }
}

void profiling_records::add_to_record_entry(std::string const & name, float time)
{
  if(p_num_record_entries == 0)
  {
    return;
  }

  auto & record = p_records[name];
  if(record.size() < p_num_record_entries)
  {
    record.resize(p_num_record_entries, 0.0f);
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

size_t profiling_records::get_num_records() const
{
  return p_records.size();
}

size_t profiling_records::get_num_record_entries() const
{
  return p_num_record_entries;
}

profiling_records::time_record const*
profiling_records::get_record(std::string const& name) const
{
  auto record_find_it = p_records.find(name);
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
  return p_max_num_record_entries;
}

void profiling_records::set_max_num_record_entries(size_t const& value)
{
  if(value < p_num_record_entries)
  {
    // If there are more existing record entries than the new maximum, shrink all existing
    //   records discarding the oldest entries.
    size_t num_to_discard = p_num_record_entries - value;
    for(auto & key_record_pair : p_records)
    {
      for(unsigned i = 0; i < num_to_discard; ++i)
      {
        key_record_pair.second.pop_front();
      }
    }

    p_num_record_entries = value;
  }

  p_max_num_record_entries = value;
}

std::ostream & operator<<(std::ostream & os, profiling_records const& rhs)
{
  for(auto const& key_record_pair : rhs)
  {
    os << fmt::format("{:<10} |", key_record_pair.first);
    for(auto const& record_entry : key_record_pair.second)
    {
      os << fmt::format(" {:>2.6f} |", record_entry);
    }
    os << std::endl;
  }

  return os;
}

} // namespace LE
