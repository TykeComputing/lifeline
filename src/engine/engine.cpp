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

#include "engine.h"

// TODO - Remove once graphics framework is in place
#include <GL/glew.h>

#include <common/LE_printf.h>

// TODO - Remove when done testing
#include <graphics/vertex.h>
#include <graphics/vertex_array.h>
#include <graphics/vertex_buffer.h>

namespace LE
{

engine::engine() :
  p_os_interface(),
  p_window(),
  p_graphics_context(p_window)
{
  LE_printf("Working Directory: %s\n", p_os_interface.get_working_dir().c_str());
}

void engine::run()
{
  // TODO - Remove when done testing
  LE::vertex_array fsq_VAO;
  LE::vertex_buffer fsq_VBO;

  LE::vertex_array::bind(fsq_VAO);
  LE::vertex_buffer::bind(GL_ARRAY_BUFFER, fsq_VBO);

  //vertex v = { 1.0f, 2.0f, 3.0f, 4.0f };
  vertex::specify_vertex_attributes();
  float fsq_verts[] =
  {
    -1.0f, -1.0f, /**/ 0.0f, 0.0f,
     1.0f, -1.0f, /**/ 1.0f, 0.0f,
    -1.0f,  1.0f, /**/ 0.0f, 1.0f,

    -1.0f,  1.0f, /**/ 0.0f, 1.0f,
     1.0f, -1.0f, /**/ 1.0f, 0.0f,
     1.0f,  1.0f, /**/ 1.0f, 1.0f
  };
  GLsizei num_fsq_verts = sizeof(fsq_verts) / (sizeof(float) * 4);
  ///////////////////////
  /// \brief glClearColor

  LE::vertex_buffer::set_data(GL_ARRAY_BUFFER, sizeof(fsq_verts), fsq_verts, GL_STATIC_DRAW);

  glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

  p_is_running = true;
  while(p_is_running)
  {
    // Update
    // Temp hack to allow quiting
    set_is_running(p_os_interface.update());

    // Render
    // TODO - Move once graphics framework is in place
    glClear(GL_COLOR_BUFFER_BIT);

    LE::vertex_buffer::draw_arrays(GL_TRIANGLES, 0, num_fsq_verts);

    p_window.update();
  }
}

void engine::set_is_running(bool val)
{
  p_is_running = val;
}

} // namespace LE
