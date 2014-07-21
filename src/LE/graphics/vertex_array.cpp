/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "vertex_array.h"

#include <utility>

namespace LE
{

vertex_array::vertex_array()
{
  glGenVertexArrays(1, &p_raw_name);
}

vertex_array::~vertex_array()
{
  glDeleteVertexArrays(1, &p_raw_name);
}

void vertex_array::bind(vertex_array const& VAO)
{
  glBindVertexArray(VAO.p_raw_name);
}

void vertex_array::unbind()
{
  glBindVertexArray(0);
}

} // namespace LE
