/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "renderable_buffer.h"

namespace LE
{

void renderable_array_buffer::bind() const
{
  vertex_array::bind(p_VAO);
}

void renderable_array_buffer::unbind() const
{
  vertex_array::unbind();
}

GLsizei renderable_array_buffer::get_num_verts() const
{
  return p_num_verts;
}

void renderable_element_buffer::bind() const
{
  vertex_array::bind(p_VAO);
}

void renderable_element_buffer::unbind() const
{
  vertex_array::unbind();
}

GLsizei renderable_element_buffer::get_num_verts() const
{
  return p_num_verts;
}

} // namespace LE
