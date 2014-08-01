/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "renderable_array.h"

namespace LE
{

void renderable_array::bind() const
{
  vertex_array::bind(p_VAO);
}

void renderable_array::unbind() const
{
  vertex_array::unbind();
}

GLsizei renderable_array::get_num_verts() const
{
  return p_num_verts;
}

} // namespace LE
