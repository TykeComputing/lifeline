/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "vertex.h"

#include <cstddef> // offsetof

#include <graphics/vertex_buffer.h>

namespace LE
{

vertex::vertex(vec2 const& position, vec2 const& texcoord) :
  position(position), texcoord(texcoord)
{

}

void vertex::specify_vertex_attributes()
{
  vertex_buffer::specify_vertex_attrtibute(
    vertex_attrib_type::position,
    decltype(position)::size, GL_FLOAT, GL_FALSE,
    sizeof(vertex), offsetof(vertex, position));

  vertex_buffer::specify_vertex_attrtibute(
    vertex_attrib_type::texcoord,
    decltype(texcoord)::size, GL_FLOAT, GL_FALSE,
    sizeof(vertex), offsetof(vertex, texcoord));
}

debug_shape_vertex::debug_shape_vertex(vec2 const& position, vec4 const& color) :
  position(position), color(color)
{

}

void debug_shape_vertex::specify_vertex_attributes()
{
  vertex_buffer::specify_vertex_attrtibute(
    vertex_attrib_type::position,
    decltype(position)::size, GL_FLOAT, GL_FALSE,
    sizeof(debug_shape_vertex), offsetof(debug_shape_vertex, position));

  vertex_buffer::specify_vertex_attrtibute(
    vertex_attrib_type::color,
    decltype(color)::size, GL_FLOAT, GL_FALSE,
    sizeof(debug_shape_vertex), offsetof(debug_shape_vertex, color));
}

} // namespace LE
