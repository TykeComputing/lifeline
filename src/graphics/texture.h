/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_GRAPHICS_TEXTURE_H
#define LE_GRAPHICS_TEXTURE_H

#include <string>
#include <GL/glew.h>

namespace LE
{

// TODO - URGENT Refactor interface to follow conventions established by vertex_buffer.
class texture
{
public:
  texture();
  ~texture();

  static void set_active_unit(GLuint unit_index);

  static void bind(GLenum target, texture const& tex);
  static void unbind(GLenum target);

  static void set_data(
    GLenum target,
    GLint level,
    GLint internal_format,
    GLsizei width,
    GLsizei height,
    GLenum format,
    GLenum type,
    GLvoid const* data);

  static void set_parameter(GLenum target, GLenum param_name, GLint param_value);

private:
  GLuint p_raw_name = 0;
};

class texture2D
{
public:
  texture2D();
  explicit texture2D(std::string const& texture_file_name);

  void load_texture_file(std::string const& texture_file_name);

  static void bind(texture2D const& tex2D);
  static void unbind();

  static void set_data(
    GLint internal_format,
    GLsizei width,
    GLsizei height,
    GLenum format,
    GLenum type,
    GLvoid const* data);

  static void set_parameter(GLenum param_name, GLint param_value);

private:
  // Composition to disallow conversion from texture2D to texture (which would allow binding to
  //   other targets). TODO - Evalute this decision after using.
  texture p_texture;
};

} // namespace LE

#endif // LE_GRAPHICS_TEXTURE_H
