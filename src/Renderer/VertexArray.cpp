#include "../precompiledheader.h"
#include <glad/glad.h>
#include "VertexArray.h"

VertexArray::VertexArray() {
  glGenVertexArrays(1, &rendererID);
}

void VertexArray::enableAttribute(unsigned int index) const {
  glEnableVertexAttribArray(index);
}

void VertexArray::describeAttributeLayout(unsigned int attributeIndex, int size, GLenum type, bool normalized, int stride, int offset) const {
  glVertexAttribPointer(attributeIndex, size, type, normalized, stride, (void*)offset);
}

void VertexArray::bind() const {
  glBindVertexArray(rendererID);
}

void VertexArray::unbind() const {
  glBindVertexArray(0);
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &rendererID);
}