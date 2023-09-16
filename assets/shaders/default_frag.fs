#version 330 core
out vec4 FragColor;

in vec3 Colour;
// uniform sampler2D texture_sampler;

void main()
{
  // FragColor = texture(texture_sampler, TexCoords);
  FragColor = vec4(Colour, 1.0);
}