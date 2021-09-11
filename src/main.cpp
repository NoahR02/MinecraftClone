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

                                   uniform mat4 uProjection;

                                   void main() {
                                     outColor = color;
                                     outTextureCoordinates = textureCoordinates;
                                     gl_Position = uProjection * vec4(pos, 1.0f);
                                   })Shader";


  const char* fragmentShaderString = R"Shader(#version 330 core
                                     in vec4 outColor;
                                     in vec2 outTextureCoordinates;

                                     out vec4 fragColor;
                                     uniform sampler2D uTexture;

                                     void main() {
                                       fragColor = texture(uTexture, outTextureCoordinates) * outColor;
                                     })Shader";

  unsigned int program = glCreateProgram();

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderString, nullptr);
  glShaderSource(fragmentShader, 1, &fragmentShaderString, nullptr);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  glUseProgram(program);

  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;


  int width;
  int height;
  int channels;

  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load("assets/textures/test.png", &width, &height, &channels, 4);

  unsigned int texture;
  glGenTextures(1, &texture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  stbi_image_free(data);

  std::vector<float> vertices = {
    // Positions,                  Colors,                         Texture Coordinates
    200.0f, 100.0f, 0.0f,             1.0f, 0.5f, 1.0f, 1.0f,            0.0f, 1.0f,               // Top Left
    200.0f, 300.0f, 0.0f,            1.0f, 0.2f, 0.0f, 1.0f,            0.0f, 0.0f,               // Bottom Left
    400.0f, 100.0f, 0.0f,              0.2f, 0.0f, 0.8f, 1.0f,            1.0f, 1.0f,               // Top Right
    400.0f, 300.0f, 0.0f,             0.4f, 0.5f, 1.0f, 1.0f,            1.0f, 0.0f,               // Bottom Right
  };

  std::vector<unsigned int> indices = {
    0, 1, 2,
    2, 1, 3,
  };


  glm::mat4 projection = glm::ortho(0.0f, window.width, window.height, 0.0f);


  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)nullptr);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(sizeof(float) * 3));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(sizeof(float) * 7));

  glUseProgram(program);
  glBindTexture(GL_TEXTURE_2D, texture);
  glUniform1i(glGetUniformLocation(program, "uTexture"), 0);
  glUniformMatrix4fv(glGetUniformLocation(program, "uProjection"), 1, GL_FALSE, glm::value_ptr(projection));

  while(!window.shouldClose()) {
    glClearColor(181/255.0f, 81/255.0f, 81/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

    window.pollEvents();
    window.swapBuffers();
  }

  window.cleanup();
}