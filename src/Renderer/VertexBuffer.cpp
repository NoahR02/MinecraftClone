#include "../precompiledheader.h"
#include <glad/glad.h>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() {
  glGenBuffers(1, &rendererID);
}

void VertexBuffer::bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}

void VertexBuffer::unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::uploadBufferData(const std::vector<float>& vertices, GLenum drawType) const {
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices.front(), drawType);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &rendererID);
}