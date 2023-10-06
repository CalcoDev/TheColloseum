#version 330 core

in float v_tex_idx;
in vec2 v_tex_coords;

out vec4 FragColor;

uniform sampler2D u_tex;

void main()
{
  FragColor = texture(u_tex, v_tex_coords);
}