/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/

#include "error_checking.h"

namespace LE
{

std::string get_GL_errors()
{
  return get_GL_errors(glGetError());
}

std::string get_GL_errors(GLenum last_error)
{
  std::string error_string;
  while(last_error != GL_NO_ERROR)
  {
    error_string += std::to_string(last_error);

    last_error = glGetError();

    if(last_error != GL_NO_ERROR)
    {
      error_string.append(", ");
    }
  }
  return error_string;
}

} // namespace LE
