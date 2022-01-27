#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 textureCoordinates;

out vec2 outTextureCoordinates;

uniform mat4 uMVP;

void main() {
  outTextureCoordinates = textureCoordinates;
  gl_Position = uMVP * vec4(pos, 1.0f);
}