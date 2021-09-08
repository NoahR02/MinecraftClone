#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

  while(!window.shouldClose()) {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    window.pollEvents();
    window.swapBuffers();
  }

  window.cleanup();
}