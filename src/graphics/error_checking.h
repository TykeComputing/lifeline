/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#ifndef LE_GRAPHICS_ERROR_CHECKING_H
#define LE_GRAPHICS_ERROR_CHECKING_H

#include <GL/glew.h>

#include <string>

#include <common/fatal_error.h>

#define LE_FATAL_ERROR_IF_GL_ERROR() \
{ \
  GLenum last_error = glGetError(); \
  if(last_error != GL_NO_ERROR) \
  { \
    LE_FATAL_ERROR("Internal OpenGL Error!\nCode(s): " + LE::get_GL_errors(last_error)); \
  } \
}

namespace LE
{

std::string get_GL_errors();
std::string get_GL_errors(GLenum last_error);

}

#endif // LE_GRAPHICS_ERROR_CHECKING_H
