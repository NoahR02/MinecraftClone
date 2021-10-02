#include "../precompiledheader.h"
#include <glad/glad.h>
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string& vertexShaderString, const std::string& fragmentShaderString) {
  rendererID = glCreateProgram();

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  const char* vertexShaderStringTemp = vertexShaderString.c_str();
  const char* fragmentShaderStringTemp = fragmentShaderString.c_str();

  glShaderSource(vertexShader, 1, &vertexShaderStringTemp, nullptr);
  glShaderSource(fragmentShader, 1, &fragmentShaderStringTemp, nullptr);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  glAttachShader(rendererID, vertexShader);
  glAttachShader(rendererID, fragmentShader);
  glLinkProgram(rendererID);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void ShaderProgram::uniform1i(const std::string& uniformName, int uniformData) const {
  glUniform1i(glGetUniformLocation(rendererID, uniformName.c_str()), uniformData);
}

void ShaderProgram::uniformMatrix4fv(const std::string& uniformName, int count, bool transpose, const float* uniformData) const {
  glUniformMatrix4fv(glGetUniformLocation(rendererID, uniformName.c_str()), count, transpose, uniformData);
}

void ShaderProgram::bind() const {
  glUseProgram(rendererID);
}

void ShaderProgram::unbind() const {
  glUseProgram(0);
}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(rendererID);
}