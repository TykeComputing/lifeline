/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/
#version 150

in vec2 position;
in vec4 color;

out vec4 v_color;

uniform mat3 to_NDC;

void main()
{
  v_color = color;
  gl_Position = vec4(to_NDC * vec3(position, 1.0f), 1.0f);
}
