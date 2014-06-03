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

#include <cstdio>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <common/error.h>
#include <common/fatal_construction_exception.h>
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

int main(int arg_count, char *args[])
{
  LE_UNUSED_VAR(arg_count);
  LE_UNUSED_VAR(args);

  try
  {
    LE::engine game_engine;

    // TODO - Move shader loading to someplace that makes more sense once resources exist
    // Load shaders
    std::vector<LE::shader *> shaders;
    try
    {      
      shaders.emplace_back(
        new LE::shader(GL_VERTEX_SHADER, std::vector<std::string>(1, "resources/shaders/solid_color.vert")) );
      shaders.emplace_back(
        new LE::shader(GL_FRAGMENT_SHADER, std::vector<std::string>(1, "resources/shaders/solid_color.frag")) );
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
