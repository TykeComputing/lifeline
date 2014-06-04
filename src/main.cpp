/*
************************************************************************************************
Copyright 2014 Peter Clark

This file is part of Lifeline Engine.

Lifeline Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Lifeline Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Lifeline Engine.  If not, see <http://www.gnu.org/licenses/>.
************************************************************************************************
*/

#include <map>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <common/error.h>
#include <common/fatal_construction_exception.h>
#include <common/LE_printf.h>
#include <common/macros.h>
#include <engine/engine.h>

// TODO - REMOVE AFTER TESTING
#include <graphics/shader_program.h>
#include <string>
#include <vector>
#include <common/resource_exception.h>
#include <graphics/vertex.h>
#include <graphics/vertex_array.h>
#include <graphics/vertex_buffer.h>

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
    if(arg_value_separator_pos == std::string::npos || arg_value_separator_pos >= curr_arg.size())
    {
      LE_printf("Malformed option specified: \"%s\"\n", curr_arg.c_str());
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
      LE_printf("Invalid option specified: \"%s\"\n", curr_arg.c_str());
    }
  }
}

int main(int arg_count, char *args[])
{
  try
  {
    LE::engine game_engine;

    handle_args(game_engine,  arg_count, args);

    // TODO - Move shader loading to someplace that makes more sense once resources exist
    // Load shaders
    std::vector<LE::shader *> shaders;
    try
    {      
      shaders.emplace_back(
        new LE::shader(GL_VERTEX_SHADER, std::vector<std::string>(1, game_engine.get_resource_dir() + "shaders/solid_color.vert")) );
      shaders.emplace_back(
        new LE::shader(GL_FRAGMENT_SHADER, std::vector<std::string>(1, game_engine.get_resource_dir() + "shaders/solid_color.frag")));
    }
    catch(LE::resource_exception const& e)
    {
      e.print("Shader Loading");
      LE_ERROR("Unable to compile shaders!"); // TODO - Remove
      return -1;
    }

    // Load shader_program
    LE::shader_program * solid_color = nullptr;
    try
    {
      solid_color = new LE::shader_program(shaders);
    }
    catch (LE::resource_exception const& e)
    {
      e.print("Shader Program Loading");
      LE_ERROR("Unable to link shaders!"); // TODO - Remove
      return -1;
    }

    shaders.clear();
    LE::shader_program::use(*solid_color);

    game_engine.run();
  }
  catch(LE::fatal_construction_exception const& e)
  {
    e.print("Engine Creation");
    LE_ERROR("Unable to create engine!"); // TODO - Remove
    return -1;
  }

  return 0;
}
