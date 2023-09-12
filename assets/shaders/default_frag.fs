#version 330 core
out vec4 FragColor;

uniform float time;
uniform vec3 colour;

void main()
{
  float r = sin(time);
  float g = cos(time);
  float b = 1.0f;
  FragColor = vec4(r, g, colour.z, 1.0f);
}