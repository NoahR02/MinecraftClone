#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include <stb_image/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

struct Window {

  Window(const Window &) = delete;

  GLFWwindow* glfwWindow;
  float width;
  float height;
  std::string title;

  Window(float width, float height, const std::string& title) : width(width), height(height), title(title) {}

  int init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if(glfwWindow == nullptr) {
      std::cout << "Failed to create a glfw window." << std::endl;
      cleanup();
      return -1;
    }

    glfwMakeContextCurrent(glfwWindow);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize glad." << std::endl;
      cleanup();
      return -1;
    }

    glfwSetFramebufferSizeCallback(glfwWindow, framebufferSizeCallback);

    return 0;
  }

  bool shouldClose() const {
    return glfwWindowShouldClose(glfwWindow);
  };

  void swapBuffers() const {
    glfwSwapBuffers(glfwWindow);
  }

  void pollEvents() {
    glfwPollEvents();
  }

  void cleanup() const {
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
  }

private:
  Window() = delete;

};


struct VertexArray {

  unsigned int rendererID;

  VertexArray() {
    glGenVertexArrays(1, &rendererID);
  }

  void enableAttribute(unsigned int index) const {
    glEnableVertexAttribArray(index);
  }

  void describeAttributeLayout(unsigned int attributeIndex, int size, GLenum type, bool normalized, int stride, int offset) const {
    glVertexAttribPointer(attributeIndex, size, type, normalized, stride, (void*)offset);
  }

  void bind() const {
    glBindVertexArray(rendererID);
  }

  void unbind() const {
    glBindVertexArray(0);
  }

  ~VertexArray() {
    glDeleteVertexArrays(1, &rendererID);
  }

};

struct VertexBuffer {

  unsigned int rendererID;

  VertexBuffer() {
    glGenBuffers(1, &rendererID);
  }

  void bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
  }

  void unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void uploadBufferData(const std::vector<float>& vertices, GLenum drawType) const {
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices.front(), drawType);
  }

  ~VertexBuffer() {
    glDeleteBuffers(1, &rendererID);
  }

};

struct IndexBuffer {

  unsigned int rendererID;

  IndexBuffer() {
    glGenBuffers(1, &rendererID);
  }

  void bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
  }

  void unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void uploadBufferData(const std::vector<unsigned int>& indices, GLenum drawType) const {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), &indices.front(), drawType);
  }

  ~IndexBuffer() {
    glDeleteBuffers(1, &rendererID);
  }

};

struct ShaderProgram {

  unsigned int rendererID;

  ShaderProgram(const std::string& vertexShaderString, const std::string& fragmentShaderString) {
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

  void uniform1i(const std::string& uniformName, int uniformData) const {
    glUniform1i(glGetUniformLocation(rendererID, uniformName.c_str()), uniformData);
  }

  void uniformMatrix4fv(const std::string& uniformName, int count, bool transpose, const float* uniformData) const {
    glUniformMatrix4fv(glGetUniformLocation(rendererID, uniformName.c_str()), count, transpose, uniformData);
  }

  //glUniform1i(glGetUniformLocation(program.rendererID, "uTexture"), 0);
 // glUniformMatrix4fv(glGetUniformLocation(program.rendererID, "uMVP"), 1, GL_FALSE, glm::value_ptr(mvp));

  void bind() const {
    glUseProgram(rendererID);
  }

  void unbind() const {
    glUseProgram(0);
  }

  ~ShaderProgram() {
    glDeleteProgram(rendererID);
  }

};

struct Texture {

  unsigned int rendererID;

  int width;
  int height;
  int channels;

  Texture(const std::string& texturePath) {
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

  void bind() const {
    glBindTexture(GL_TEXTURE_2D, rendererID);
  }

  void unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  ~Texture() {
    glDeleteTextures(1, &rendererID);
  }

};

int main() {
  Window window(1600, 900, "MinecraftClone");

  if(window.init() == -1) {
    return -1;
  }


  const char* vertexShaderString = R"Shader(#version 330 core
                                   layout (location = 0) in vec3 pos;
                                   layout (location = 1) in vec4 color;
                                   layout (location = 2) in vec2 textureCoordinates;

                                   out vec4 outColor;
                                   out vec2 outTextureCoordinates;

                                   uniform mat4 uMVP;

                                   void main() {
                                     outColor = color;
                                     outTextureCoordinates = textureCoordinates;
                                     gl_Position = uMVP * vec4(pos, 1.0f);
                                   })Shader";
  const char* fragmentShaderString = R"Shader(#version 330 core
                                     in vec4 outColor;
                                     in vec2 outTextureCoordinates;

                                     out vec4 fragColor;
                                     uniform sampler2D uTexture;

                                     void main() {
                                       fragColor = texture(uTexture, outTextureCoordinates) * outColor;
                                     })Shader";

  ShaderProgram program(vertexShaderString, fragmentShaderString);

  VertexArray vao;
  VertexBuffer vbo;
  IndexBuffer ibo;

  VertexBuffer cubeVBO;
  VertexArray cubeVAO;

  Texture texture("assets/textures/test.png");

  std::vector<float> cube = {

    // Front Face.
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    // Side Face(Visible)
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,

    // Top Face
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,

    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,

    // Side Face (Not Visible)
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,

    0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f,

    // Back Face
    0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f,

    // Bottom Face
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f,
  };

  std::vector<float> vertices = {
    // Positions,                  Colors,                         Texture Coordinates
    -0.5f, 0.5f, 0.0f,             1.0f, 0.5f, 1.0f, 1.0f,            0.0f, 1.0f,               // Top Left
    -0.5f, -0.5f, 0.0f,            1.0f, 0.2f, 0.0f, 1.0f,            0.0f, 0.0f,               // Bottom Left
    0.5f, 0.5f, 0.0f,              0.2f, 0.0f, 0.8f, 1.0f,            1.0f, 1.0f,               // Top Right
    0.5f, -0.5f, 0.0f,             0.4f, 0.5f, 1.0f, 1.0f,            1.0f, 0.0f,               // Bottom Right
  };

  std::vector<unsigned int> indices = {
    0, 1, 2,
    2, 1, 3,
  };



  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

  projection = glm::perspective(glm::radians(45.0f), window.width / window.height, 0.1f, 100.0f);
  //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3{0.0f, 0.0f, 0.0f});
  view = glm::translate(view, glm::vec3{0.0f, 0.0f, -3.0f});

  glm::mat4 mvp = projection * view * model;


  vao.bind();
  vbo.bind();

  ibo.bind();

  vbo.uploadBufferData(vertices, GL_STATIC_DRAW);
  ibo.uploadBufferData(indices, GL_STATIC_DRAW);


  vao.enableAttribute(0);
  vao.describeAttributeLayout(0, 3, GL_FLOAT, false, sizeof(float) * 9, 0);

  vao.enableAttribute(1);
  vao.describeAttributeLayout(1, 4, GL_FLOAT, false, sizeof(float) * 9, (sizeof(float) * 3));

  vao.enableAttribute(2);
  vao.describeAttributeLayout(2, 2, GL_FLOAT, false, sizeof(float) * 9, (sizeof(float) * 7));


  const char* vertexShaderStringCUBE = R"Shader(#version 330 core
                                   layout (location = 0) in vec3 pos;
                                   uniform mat4 uMVP;

                                   void main() {
                                     gl_Position = uMVP * vec4(pos, 1.0f);
                                   })Shader";


  const char* fragmentShaderStringCUBE = R"Shader(#version 330 core

                                     out vec4 fragColor;

                                     void main() {
                                       fragColor = vec4(1.0f, 0.5f, 0.0f, 1.0f);
                                     })Shader";

  ShaderProgram programCUBE(vertexShaderStringCUBE, fragmentShaderStringCUBE);

  cubeVAO.bind();
  cubeVBO.bind();
  cubeVBO.uploadBufferData(cube, GL_STATIC_DRAW);
  cubeVAO.enableAttribute(0);
  cubeVAO.describeAttributeLayout(0, 3, GL_FLOAT, false, 0, 0);

  glm::mat4 modelCUBE = glm::mat4(1.0f);
  glm::mat4 viewCUBE = glm::mat4(1.0f);
  glm::mat4 projectionCUBE = glm::mat4(1.0f);

  projectionCUBE = glm::perspective(glm::radians(45.0f), window.width / window.height, 0.1f, 100.0f);
  modelCUBE = glm::scale(modelCUBE, glm::vec3{0.5f, 0.5f, 0.5f});
  modelCUBE = glm::rotate(modelCUBE, glm::radians(75.0f), glm::vec3{1.0f, 0.0f, 0.0f});
  modelCUBE = glm::translate(modelCUBE, glm::vec3{0.9f, 0.0f, 0.0f});
  viewCUBE = glm::translate(viewCUBE, glm::vec3{0.0f, 0.0f, -3.0f});

  glm::mat4 mvpCUBE = projectionCUBE * viewCUBE * modelCUBE;

  programCUBE.bind();
  programCUBE.uniformMatrix4fv("uMVP", 1, GL_FALSE, glm::value_ptr(mvpCUBE));

  while(!window.shouldClose()) {
    glClearColor(181/255.0f, 81/255.0f, 81/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    model = glm::translate(model, glm::vec3{0.0f, 0.0f, -0.1f});
    mvp = projection * view * model;

    program.bind();
    vao.bind();
    texture.bind();
    program.uniform1i("uTexture", 0);
    program.uniformMatrix4fv("uMVP", 1, false, glm::value_ptr(mvp));
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

    programCUBE.bind();
    cubeVAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, cube.size());


    window.pollEvents();
    window.swapBuffers();
  }

  window.cleanup();
}