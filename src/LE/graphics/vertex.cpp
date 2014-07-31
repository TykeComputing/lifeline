/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "vertex.h"

#include <cstddef> // offsetof

#include <LE/graphics/vertex_buffer.h>

namespace LE
{

namespace vertex
{

pos2::pos2(vec2 const& position) :
  position(position)
{

}

void pos2::specify_vertex_attributes()
{
  vertex_buffer::specify_vertex_attrtibute(
    vertex_attrib_type::position,
    decltype(position)::size, GL_FLOAT, GL_FALSE,
    sizeof(pos2), offsetof(pos2, position));
}

pos2_tex2::pos2_tex2(vec2 const& position, vec2 const& texcoord) :
  position(position), texcoord(texcoord)
{

}

void pos2_tex2::specify_vertex_attributes()
{
  vertex_buffer::specify_vertex_attrtibute(
    vertex_attrib_type::position,
    decltype(position)::size, GL_FLOAT, GL_FALSE,
    sizeof(pos2_tex2), offsetof(pos2_tex2, position));

  vertex_buffer::specify_vertex_attrtibute(
    vertex_attrib_type::texcoord,
    decltype(texcoord)::size, GL_FLOAT, GL_FALSE,
    sizeof(pos2_tex2), offsetof(pos2_tex2, texcoord));
}

pos2_col4::pos2_col4(vec2 const& position, vec4 const& color) :
  position(position), color(color)
{

}

void pos2_col4::specify_vertex_attributes()
{
  vertex_buffer::specify_vertex_attrtibute(
    vertex_attrib_type::position,
    decltype(position)::size, GL_FLOAT, GL_FALSE,
    sizeof(pos2_col4), offsetof(pos2_col4, position));

  vertex_buffer::specify_vertex_attrtibute(
    vertex_attrib_type::color,
    decltype(color)::size, GL_FLOAT, GL_FALSE,
    sizeof(pos2_col4), offsetof(pos2_col4, color));
}

}

} // namespace LE
