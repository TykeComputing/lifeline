/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/
#version 150

noperspective in vec2 v_texcoord;

out vec4 f_color;

uniform sampler2D texture;

void main()
{
  vec3 texture_color = texture2D(texture, v_texcoord).rgb;
  f_color.rgb = texture_color;
  f_color.a = 1.0f;
}
