#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 tex_coords;
layout (location = 2) in float tex_idx;

uniform mat4 view;
uniform mat4 projection;

out vec3 Colour;

void main()
{
  gl_Position = projection * view * vec4(pos.xy, 0.0, 1.0);
  Colour = vec3(1.0, 1.0, 1.0);
}