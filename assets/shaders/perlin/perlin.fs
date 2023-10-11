#version 330 core

flat in float v_tex_idx;
in vec2 v_tex_coords;

out vec4 FragColor;

uniform sampler2D u_tex[8];

void main()
{
  FragColor = vec4(0.2, 0.6, 0.4, 1.0);
}