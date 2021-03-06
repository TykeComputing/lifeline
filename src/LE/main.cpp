/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include <unordered_map>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <LE/common/fatal_error.h>
#include <LE/common/fatal_construction_exception.h>
#include <LE/common/logging.h>
#include <LE/common/macros.h>
#include <LE/common/resource_manager.h>

#include <LE/engine/engine.h>

#include <LE/devui/perf_vis.h>

#include <LE/game/game_hack.h>

typedef void(*handle_arg_func)(std::string const& val);

void handle_set_resource_dir(std::string const& val)
{
  LE::resource_manager::set_resource_dir(val);
}

void handle_args(int arg_count, char *args[])
{
  std::unordered_map<std::string, handle_arg_func> options(
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
      LE::log_error(LE::log_scope::GLOBAL, "Malformed option specified: \"{}\"", curr_arg);
      continue;
    }

    std::string curr_val(curr_arg, arg_value_separator_pos + 1);
    curr_arg.erase(arg_value_separator_pos);

    // Call appropriate handler if one exists
    auto handler_find_it = options.find(curr_arg);
    if(handler_find_it != options.end())
    {
      handler_find_it->second(curr_val);
    }
    else
    {
      LE::log_error(LE::log_scope::GLOBAL, "Invalid option specified: \"{}\"", curr_arg);
    }
  }
}

int main(int arg_count, char *args[])
{
  int res = 0;

  handle_args(arg_count, args);

  try
  {
    LE::engine game_engine;

    auto * perf_vis_space = game_engine.create_space("perf_vis");
    auto * perf_vis_ent = perf_vis_space->create_entity("perf_vis");
    perf_vis_ent->create_component<LE::perf_vis>();
    perf_vis_space->set_is_active(false);
    perf_vis_space->set_ddraw_enabled(true);

    auto * game_space = game_engine.create_space("game");
    auto * game_hack_ent = game_space->create_entity("game_hack");
    game_hack_ent->create_component<LE::game_hack>();

    game_engine.run();
  }
  catch(LE::fatal_construction_exception const&)
  {
    LE_FATAL_ERROR("Unable to create engine!"); // TODO - Remove
    res = -1;
  }

  LE::log_status(LE::log_scope::GLOBAL, "Exiting...");
  return res;
}
