#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoords;
out vec2 TexCoords;

uniform mat4 finalMat;

void main()
{
  gl_Position = finalMat * vec4(pos.xyz, 1.0);
  TexCoords = vec2(texCoords.x, texCoords.y);
  // gl_Position = vec4(pos.xyz, 1.0);
}