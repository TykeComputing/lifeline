#version 150

in vec2 position;
in vec2 texcoord;

noperspective out vec2 v_texcoord;

void main()
{
  v_texcoord = texcoord;
  gl_Position = vec4(position, 1.0f, 1.0f);
}
