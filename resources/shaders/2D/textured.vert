/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/
#version 150

in vec2 position;
in vec2 texcoord;

noperspective out vec2 v_texcoord;

uniform mat3 to_NDC;

void main()
{
  v_texcoord = texcoord;
  gl_Position = vec4(to_NDC * vec3(position, 1.0f), 1.0f);
}
