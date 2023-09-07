#version 330 core
out vec4 FragColor;

in vec4 vertex_colour;

// uniform vec4 cpu_colour;

void main()
{
  // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
  // FragColor = cpu_colour;
  FragColor = vertex_colour;
}