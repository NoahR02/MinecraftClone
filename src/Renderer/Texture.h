#ifndef MINECRAFTCLONE_TEXTURE_H
#define MINECRAFTCLONE_TEXTURE_H

#include <string>

struct Texture {

  unsigned int rendererID;

  int width;
  int height;
  int channels;

  Texture(const std::string& texturePath);

  void bind() const;
  void unbind() const;

  ~Texture();

};

#endif
