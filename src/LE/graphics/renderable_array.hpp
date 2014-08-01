/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

namespace LE
{

template<typename VERTEX_T>
void renderable_array::set_data(VERTEX_T const* verts, size_t num_verts, GLenum usage)
{
  vertex_array::bind(p_VAO);
  vertex_buffer::bind(GL_ARRAY_BUFFER, p_VBO);

  VERTEX_T::specify_vertex_attributes();
  p_num_verts = num_verts;

  vertex_buffer::set_data(
    GL_ARRAY_BUFFER,
    sizeof(VERTEX_T) * num_verts,
    verts,
    usage);

  vertex_array::unbind();
}

}
