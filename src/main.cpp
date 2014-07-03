/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include <map>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <common/fatal_error.h>
#include <common/fatal_construction_exception.h>
#include <common/logging.h>
#include <common/macros.h>
#include <engine/engine.h>

// TODO - REMOVE
#include <common/profiling_records.h>
#include <assert.h>

typedef void(*handle_arg_func)(LE::engine & game_engine, std::string const& val);

void handle_set_resource_dir(LE::engine & game_engine, std::string const& val)
{
  game_engine.set_resource_dir(val);
}

void handle_args(LE::engine & game_engine, int arg_count, char *args[])
{
  std::map<std::string, handle_arg_func> options(
  {
    { "--resource-dir", handle_set_resource_dir }
  });

  for(auto arg_it = 1; arg_it < arg_count; ++arg_it)
  {
    std::string curr_arg(args[arg_it]);

    // Transform input from `--<arg_name>=<value>` to `--<arg_name>` and `<value>`
    auto arg_value_separator_pos = curr_arg.find('=');
    if(arg_value_separator_pos == std::string::npos
    || arg_value_separator_pos >= curr_arg.size())
    {
      LE::log_error(LE::log_scope::GLOBAL, "Malformed option specified: \"{}\"") << curr_arg;
      continue;
    }

    std::string curr_val(curr_arg, arg_value_separator_pos + 1);
    curr_arg.erase(arg_value_separator_pos);

    // Call appropriate handler if one exists
    auto handler_find_it = options.find(curr_arg);
    if(handler_find_it != options.end())
    {
      handler_find_it->second(game_engine, curr_val);
    }
    else
    {
      LE::log_error(LE::log_scope::GLOBAL, "Invalid option specified: \"{}\"") << curr_arg;
    }
  }
}

int main(int arg_count, char *args[])
{
  int res = 0;

  try
  {
    LE::engine game_engine;

    handle_args(game_engine,  arg_count, args);

    game_engine.run();
  }
  catch(LE::fatal_construction_exception const& e)
  {
    LE::log_error(LE::log_scope::GLOBAL, "{}") << e.what();
    LE_FATAL_ERROR("Unable to create engine!"); // TODO - Remove
    res = -1;
  }

  // Quick and dirty unit test
  LE::log_status(LE::log_scope::GLOBAL, "Exiting...");

  LE::profiling_records pr;
  pr.set_max_num_record_entries(5);

  pr.start_new_record_entry();
  pr.add_to_record_entry("test1", 1.0f);
  pr.add_to_record_entry("test2", 1.0f);

  pr.start_new_record_entry();
  pr.add_to_record_entry("test1", 2.0f);
  pr.add_to_record_entry("test2", 2.0f);

  pr.start_new_record_entry();
  pr.add_to_record_entry("test1", 3.0f);
  pr.add_to_record_entry("test2", 3.0f);

  pr.start_new_record_entry();
  pr.add_to_record_entry("test1", 4.0f);
  pr.add_to_record_entry("test2", 4.0f);

  pr.start_new_record_entry();
  pr.add_to_record_entry("test1", 5.0f);
  pr.add_to_record_entry("test2", 5.0f);

  pr.start_new_record_entry();
  pr.add_to_record_entry("test2", 6.0f);

  pr.start_new_record_entry();
  pr.add_to_record_entry("test2", 7.0f);


  auto const* t1 = pr.get_record("test1");
  assert(t1 != nullptr);
  assert((*t1)[0] == 3.0f);
  assert((*t1)[1] == 4.0f);
  assert((*t1)[2] == 5.0f);
  assert((*t1)[3] == 0.0f);
  assert((*t1)[4] == 0.0f);
  auto const* t2 = pr.get_record("test2");
  assert(t2 != nullptr);
  assert((*t2)[0] == 3.0f);
  assert((*t2)[1] == 4.0f);
  assert((*t2)[2] == 5.0f);
  assert((*t2)[3] == 6.0f);
  assert((*t2)[4] == 7.0f);


  pr.set_max_num_record_entries(6);

  assert(t1 != nullptr);
  assert((*t1)[0] == 3.0f);
  assert((*t1)[1] == 4.0f);
  assert((*t1)[2] == 5.0f);
  assert((*t1)[3] == 0.0f);
  assert((*t1)[4] == 0.0f);

  assert(t2 != nullptr);
  assert((*t2)[0] == 3.0f);
  assert((*t2)[1] == 4.0f);
  assert((*t2)[2] == 5.0f);
  assert((*t2)[3] == 6.0f);
  assert((*t2)[4] == 7.0f);


  pr.set_max_num_record_entries(4);

  assert(t1 != nullptr);
  assert((*t1)[0] == 4.0f);
  assert((*t1)[1] == 5.0f);
  assert((*t1)[2] == 0.0f);
  assert((*t1)[3] == 0.0f);

  assert(t2 != nullptr);
  assert((*t2)[0] == 4.0f);
  assert((*t2)[1] == 5.0f);
  assert((*t2)[2] == 6.0f);
  assert((*t2)[3] == 7.0f);



  return res;
}
