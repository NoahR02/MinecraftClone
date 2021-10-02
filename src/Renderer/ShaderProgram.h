#ifndef MINECRAFTCLONE_SHADERPROGRAM_H
#define MINECRAFTCLONE_SHADERPROGRAM_H

#include <string>

struct ShaderProgram {

  unsigned int rendererID;

  ShaderProgram(const std::string& vertexShaderString, const std::string& fragmentShaderString);

  void uniform1i(const std::string& uniformName, int uniformData) const;

  void uniformMatrix4fv(const std::string& uniformName, int count, bool transpose, const float* uniformData) const;

  void bind() const;
  void unbind() const;

  ~ShaderProgram();

};


#endif
