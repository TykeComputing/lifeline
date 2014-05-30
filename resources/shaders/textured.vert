#version 330

layout(location = 0) in vec2 pos;

noperspective out vec2 v_tex;

void main()
{
  v_tex = pos * 0.5f + 0.5f;
  gl_Position = vec4(pos, 1.0f, 1.0f);
}
