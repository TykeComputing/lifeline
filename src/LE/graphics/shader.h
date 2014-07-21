/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_GRAPHICS_SHADER_H
#define LE_GRAPHICS_SHADER_H

#include <string>
#include <vector>

#include <GL/glew.h>

#include <LE/common/macros.h>

namespace LE
{

class shader
{
public:
  LE_NON_COPYABLE(shader)

  shader(GLenum type, std::vector<std::string> const& shader_soure_file_names);
  ~shader();

  std::string const& get_file_name() const;

private:
  GLuint p_raw_name = 0;
  GLenum p_type = GL_NONE;
  std::string p_file_name;

  friend class shader_program;
};

} // namespace LE

#endif // LE_GRAPHICS_SHADER_H
