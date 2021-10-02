#ifndef MINECRAFTCLONE_VERTEXBUFFER_H
#define MINECRAFTCLONE_VERTEXBUFFER_H

#include <vector>

struct VertexBuffer {

  unsigned int rendererID;

  VertexBuffer();

  void bind() const;
  void unbind() const;

  void uploadBufferData(const std::vector<float>& vertices, GLenum drawType) const;

  ~VertexBuffer();

};

#endif
