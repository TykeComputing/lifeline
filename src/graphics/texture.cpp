/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "texture.h"

#include <stb/stb_image.h>

#include <common/cppformat.h>
#include <common/macros.h>
#include <common/resource_exception.h>

#include <graphics/error_checking.h>

namespace LE
{


/**********************************************************************************************/
/* texture */
/**********************************************************************************************/

texture::texture()
{
  glGenTextures(1, &p_raw_name);
}

texture::~texture()
{
  glDeleteTextures(1, &p_raw_name);
}

ivec3 const& texture::get_dimensions() const
{
  return p_dimensions;
}

void texture::set_active_unit(GLuint unit_index)
{
  glActiveTexture(GL_TEXTURE0 + unit_index);
}

void texture::bind(GLenum target, texture const& tex)
{
  glBindTexture(target, tex.p_raw_name);
}

void texture::unbind(GLenum target)
{
  glBindTexture(target, 0);
}

void texture::set_data_2D(
  texture & tex,
  GLenum target,
  GLint level,
  GLint internal_format,
  GLsizei width,
  GLsizei height,
  GLenum format,
  GLenum type,
  GLvoid const* data)
{
  tex.p_dimensions.x() = width;
  tex.p_dimensions.y() = height;
  glTexImage2D(target, level, internal_format, width, height, 0, format, type, data);
  LE_FATAL_ERROR_IF_GL_ERROR();
}

void texture::set_parameter(GLenum target, GLenum param_name, GLint param_value)
{
  glTexParameteri(target, param_name, param_value);
  LE_FATAL_ERROR_IF_GL_ERROR();
}

/**********************************************************************************************/
/* texture2D */
/**********************************************************************************************/

texture2D::texture2D()
{
  bind(*this);

  set_parameter(GL_TEXTURE_BASE_LEVEL, 0);
  set_parameter(GL_TEXTURE_MAX_LEVEL, 0);
  set_parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  set_parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  set_parameter(GL_TEXTURE_WRAP_S, GL_CLAMP);
  set_parameter(GL_TEXTURE_WRAP_T, GL_CLAMP);

  unbind();
}

texture2D::texture2D(std::string const& texture_file_name) :
  texture2D()
{
  load_texture_file(texture_file_name);
}

void texture2D::load_texture_file(std::string const& texture_file_name)
{
  unsigned char * texture_data = nullptr;
  int w = 0, h = 0;
  int num_components_in_file = 0; LE_UNUSED_VAR(num_components_in_file);
  texture_data = stbi_load(texture_file_name.c_str(), &w, &h, &num_components_in_file, 4);

  if(texture_data == nullptr)
  {
    // NOTE: stbi_failure_reason is NOT thread safe.
    throw resource_exception( fmt::format("Texture: Unable to load texture \"{}\", {}.",
     texture_file_name, stbi_failure_reason()) );
  }

  bind(*this);
  set_data(*this, GL_SRGB8_ALPHA8, w, h, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
  stbi_image_free(texture_data);
  unbind();
  LE_FATAL_ERROR_IF_GL_ERROR();
}

ivec2 texture2D::get_dimensions() const
{
  return ivec2(p_texture.get_dimensions());
}

void texture2D::bind(texture2D const& tex2D)
{
  texture::bind(GL_TEXTURE_2D, tex2D.p_texture);
}

void texture2D::unbind()
{
  texture::unbind(GL_TEXTURE_2D);
}

void texture2D::set_data(
  texture2D & tex,
  GLint internal_format,
  GLsizei width,
  GLsizei height,
  GLenum format,
  GLenum type,
  GLvoid const* data)
{
  texture::set_data_2D(
    tex.p_texture,
    GL_TEXTURE_2D,
    0,
    internal_format,
    width,
    height,
    format,
    type,
    data);
}

void texture2D::set_parameter(GLenum param_name, GLint param_value)
{
  texture::set_parameter(GL_TEXTURE_2D, param_name, param_value);
}

} // namespace LE
