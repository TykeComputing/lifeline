/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

namespace LE
{

template<typename VERTEX_T>
void renderable_array_buffer::set_data(VERTEX_T const* verts, size_t num_verts, GLenum usage)
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

  vertex_buffer::unbind(GL_ARRAY_BUFFER);
  vertex_array::unbind();
}

template<typename VERTEX_T>
void renderable_element_buffer::set_data(
    VERTEX_T const* verts,
    size_t num_verts,
    GLuint const* indices,
    size_t num_indices,
    GLenum usage)
{
  vertex_array::bind(p_VAO);
  vertex_buffer::bind(GL_ARRAY_BUFFER, p_VBO);
  vertex_buffer::bind(GL_ELEMENT_ARRAY_BUFFER, p_IBO);

  VERTEX_T::specify_vertex_attributes();

  p_num_verts = num_verts;
  vertex_buffer::set_data(
    GL_ARRAY_BUFFER,
    sizeof(VERTEX_T) * num_verts,
    verts,
    usage);

  p_num_indices = num_indices;
  vertex_buffer::set_data(
    GL_ELEMENT_ARRAY_BUFFER,
    sizeof(GLuint) * num_indices,
    indices,
    usage);

  vertex_array::unbind();
}

}
