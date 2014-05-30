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
#include <GL/gl.h>

#include <common/fatal_construction_exception.h>
#include <engine/engine.h>

// TODO - REMOVE AFTER TESTING
#include <graphics/shader_program.h>
#include <string>
#include <vector>
#include <common/resource_exception.h>

#define LE_UNUSED_VAR(x) (void)x

int main(int arg_count, char *args[])
{
  LE_UNUSED_VAR(arg_count);
  LE_UNUSED_VAR(args);

  try
  {
    LE::engine game_engine;

    try
    {
      std::vector<LE::shader> shaders;
      shaders.emplace_back(
            GL_VERTEX_SHADER, std::vector<std::string>(1, "resources/shaders/solid_color.vert"));
      shaders.emplace_back(
            GL_FRAGMENT_SHADER, std::vector<std::string>(1, "resources/shaders/solid_color.frag"));
      LE::shader_program solid_color(shaders); LE_UNUSED_VAR(solid_color);
      shaders.clear();
      shaders.emplace_back(
            GL_VERTEX_SHADER, std::vector<std::string>(1, "resources/shaders/textured.vert"));
      shaders.emplace_back(
            GL_FRAGMENT_SHADER, std::vector<std::string>(1, "resources/shaders/textured.frag"));
      LE::shader_program textured(shaders); LE_UNUSED_VAR(textured);
      shaders.clear();
    }
    catch(LE::resource_exception const& e)
    {
      e.print("Shader Loading");
    }

    game_engine.run();
  }
  catch(LE::fatal_construction_exception const& e)
  {
    e.print("Engine Creation");
    return -1;
  }

  return 0;
}
