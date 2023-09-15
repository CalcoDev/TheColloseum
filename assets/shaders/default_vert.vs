#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 texCoords;
out vec2 TexCoords;

uniform mat4 transform;

void main()
{
  gl_Position = transform * vec4(pos.xy, 0.0, 1.0);
  TexCoords = vec2(texCoords.x, texCoords.y);
}