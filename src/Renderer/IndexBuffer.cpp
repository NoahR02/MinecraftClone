#include "../precompiledheader.h"
#include <glad/glad.h>
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer() {
  glGenBuffers(1, &rendererID);
}

void IndexBuffer::bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
}

void IndexBuffer::unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::uploadBufferData(const std::vector<unsigned int>& indices, unsigned int drawType) const {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), &indices.front(), drawType);
}

IndexBuffer::~IndexBuffer() {
  glDeleteBuffers(1, &rendererID);
}