#ifndef MINECRAFTCLONE_VERTEXARRAY_H
#define MINECRAFTCLONE_VERTEXARRAY_H


struct VertexArray {

  unsigned int rendererID;

  VertexArray();

  void enableAttribute(unsigned int index) const;
  void describeAttributeLayout(unsigned int attributeIndex, int size, unsigned int type, bool normalized, int stride, int offset) const;

  void bind() const;
  void unbind() const;
  ~VertexArray();

};

#endif
