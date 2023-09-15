#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoords;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  // pos.xyz * model -> transform local object vertex into world.
  // (prev) * view -> transform world into camera
  // (prev) * projection -> transform camera into projection
  // aka actually get all the 3d rendering goodness
  gl_Position = projection * view * model * vec4(pos.xyz, 1.0);
  TexCoords = vec2(texCoords.x, texCoords.y);
  // gl_Position = vec4(pos.xyz, 1.0);
}