/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_GRAPHICS_SHADER_PROGRAM_H
#define LE_GRAPHICS_SHADER_PROGRAM_H

#include <unordered_map>
#include <vector>

#include <GL/glew.h>

#include <LE/common/macros.h>

#include <LE/graphics/shader.h>

namespace LE
{

class shader_program
{
public:
  LE_NON_COPYABLE(shader_program)

  explicit shader_program(std::vector<shader*> const& shaders);
  ~shader_program();

  GLint get_unform_location(char const* uniform_name) const;

  static void use(shader_program & sp);
  static void use_default();
  // TODO - static set_uniform's for built in type (single and vector), and LE types (vec*, etc)

private:
  GLuint p_raw_name = 0;

  // Used to store uniform location instead of asking OpenGL every time for same result.
  mutable std::unordered_map<std::string, GLint> p_uniform_locations;
};

} // namespace LE

#endif // LE_GRAPHICS_SHADER_PROGRAM_H
