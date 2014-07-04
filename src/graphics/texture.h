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
  explicit texture(std::string const& texture_file_name);
  ~texture();

  static void set_active_texture_unit(GLuint unit_index);

  static void bind(GLenum target, texture const& tex);
  static void unbind(GLenum target);

private:
  GLuint p_raw_name = 0;
};

} // namespace LE

#endif // LE_GRAPHICS_TEXTURE_H
