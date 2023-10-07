#version 330 core

in float v_tex_idx;
in vec2 v_tex_coords;

out vec4 FragColor;

uniform sampler2D u_tex[8];

void main()
{
  switch (int(v_tex_idx)) {
    case 0: FragColor = texture(u_tex[0], v_tex_coords); break;
    case 1: FragColor = texture(u_tex[1], v_tex_coords); break;
    case 2: FragColor = texture(u_tex[2], v_tex_coords); break;
    case 3: FragColor = texture(u_tex[3], v_tex_coords); break;
    case 4: FragColor = texture(u_tex[4], v_tex_coords); break;
    case 5: FragColor = texture(u_tex[5], v_tex_coords); break;
    case 6: FragColor = texture(u_tex[6], v_tex_coords); break;
    case 7: FragColor = texture(u_tex[7], v_tex_coords); break;
    default: discard;
  }
}