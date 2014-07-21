/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_PROFILING_RECORDS_H
#define LE_COMMON_PROFILING_RECORDS_H

#include <deque>
#include <iosfwd>
#include <string>

#include <unordered_map>

#include <LE/common/macros.h>

namespace LE
{

class profiling_records
{
public:
  typedef std::deque<float> time_record;
  typedef std::unordered_map<std::string, time_record> time_record_container;

  void start_new_record_entry();

  void add_to_record_entry(std::string const& name, float time);

  time_record_container::const_iterator begin() const;
  time_record_container::const_iterator end() const;
  size_t get_num_records() const;
  size_t get_num_record_entries() const;

  time_record const* get_record(std::string const& name) const;

  size_t get_max_num_record_entries() const;
  void set_max_num_record_entries(size_t const& value);

private:
  size_t p_num_record_entries = 0;
  size_t p_max_num_record_entries = 600;
  time_record_container p_records;
};

std::ostream & operator<<(std::ostream & os, profiling_records const& rhs);

} // namespace LE

#endif // LE_COMMON_PROFILING_RECORDS_H
