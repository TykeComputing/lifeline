/*
************************************************************************************************
Copyright 2014 by Peter Clark. All Rights Reserved.
************************************************************************************************
*/
#version 150

noperspective in vec2 v_texcoord;

out vec4 f_color;

uniform sampler2D texture;
uniform vec4 color_multiplier;

void main()
{
  vec4 texture_color = texture2D(texture, v_texcoord);
  f_color.rgba = texture_color * color_multiplier;
}
