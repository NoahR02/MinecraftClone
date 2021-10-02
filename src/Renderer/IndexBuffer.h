#ifndef MINECRAFTCLONE_INDEXBUFFER_H
#define MINECRAFTCLONE_INDEXBUFFER_H

#include <vector>

struct IndexBuffer {

  unsigned int rendererID;

  IndexBuffer();

  void bind() const;
  void unbind() const;

  void uploadBufferData(const std::vector<unsigned int>& indices, unsigned int drawType) const;

  ~IndexBuffer();

};


#endif
