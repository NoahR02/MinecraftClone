#include "../precompiledheader.h"
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include "Texture.h"

Texture::Texture(const std::string& texturePath) {
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &channels, 4);

  glGenTextures(1, &rendererID);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, rendererID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  stbi_image_free(data);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() const {
  glBindTexture(GL_TEXTURE_2D, rendererID);
}

void Texture::unbind() const {
  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
  glDeleteTextures(1, &rendererID);
}