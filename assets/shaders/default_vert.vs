#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colour;

out vec3 Colour;

uniform sampler2D framebuffer;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  // gl_Position = view * model * vec4(pos.xyz, 1.0);
  gl_Position = projection * view * model * vec4(pos.xyz, 1.0);
  Colour = vec3(colour.x, colour.y, colour.z);
}