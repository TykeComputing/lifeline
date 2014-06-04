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

#include "texture.h"

#include <common/resource_exception.h>

#include <graphics/error_checking.h>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include <graphics/stb_image.h>

namespace LE
{

texture::texture(std::string const& texture_file_name)
{
  unsigned char * texture_data = nullptr;
  int w = 0, h = 0;
  int num_components_in_file = 0; // unused
  texture_data = stbi_load(texture_file_name.c_str(), &w, &h, &num_components_in_file, 4);

  if(texture_data == nullptr)
  {
    // NOTE: stbi_failure_reason is NOT thread safe.
    throw resource_exception("Material: Unable to load texture \"" + texture_file_name + "\"." + stbi_failure_reason());
  }

  glGenTextures(1, &p_raw_name);

  glBindTexture(GL_TEXTURE_2D, p_raw_name);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
  stbi_image_free(texture_data);
  LE_ERRORIF_GL_ERROR();

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  LE_ERRORIF_GL_ERROR();
}

texture::~texture()
{
  glDeleteTextures(1, &p_raw_name);
}

void texture::set_active_texture_unit(GLuint unit_index)
{
  glActiveTexture(unit_index);
}

void texture::bind(GLenum target, texture const& tex)
{
  glBindTexture(target, tex.p_raw_name);
}

void texture::unbind(GLenum target)
{
  glBindTexture(target, 0);
}

} // namespace LE
