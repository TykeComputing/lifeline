/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_COMMON_PROFILING_RECORDS_H
#define LE_COMMON_PROFILING_RECORDS_H

#include <deque>
#include <string>
#include <unordered_map>

#include <common/macros.h>

namespace LE
{

class profiling_records
{
public:
  typedef std::deque<float> time_record;
  typedef std::unordered_map<std::string, time_record> time_record_container;

  void start_record_entry();
  void end_record_entry();

  void add_to_record_entry(std::string const& label, float time);

  size_t get_max_num_record_entries() const;
  void set_max_num_record_entries(size_t const& value);

private:
  enum status
  {
    record_entry_started,
    record_entry_ended
  };

  status curr_status = record_entry_ended;
  size_t num_record_entries = 0;
  size_t max_num_record_entries = 600;
  time_record_container p_records;
};

} // namespace LE

#endif // LE_COMMON_PROFILING_RECORDS_H
