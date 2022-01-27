#version 330 core

in vec2 outTextureCoordinates;
out vec4 fragColor;
uniform sampler2D uTexture;

void main() {
  fragColor = texture(uTexture, outTextureCoordinates);
}