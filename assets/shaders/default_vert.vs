#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 colour;

out vec4 vertex_colour;

void main()
{
  vertex_colour = vec4(colour.xyz, 1.0);
  gl_Position = vec4(pos.xy, 0.0, 1.0);
}