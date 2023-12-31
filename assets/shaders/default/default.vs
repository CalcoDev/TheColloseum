#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex_coords;
layout (location = 2) in float tex_idx;

uniform mat4 view;
uniform mat4 projection;

flat out float v_tex_idx;
out vec2 v_tex_coords;

void main()
{
  gl_Position = projection * view * vec4(-pos.x, pos.y, pos.z, 1.0);
  v_tex_idx = tex_idx;
  v_tex_coords = tex_coords;
}