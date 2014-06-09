#version 150

in vec2 position;

uniform mat3 model_to_world;

void main()
{
  gl_Position = vec4(model_to_world * vec3(position, 1.0f), 1.0f);
}
