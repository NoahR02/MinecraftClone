#include "precompiledheader.h"
#include <glad/glad.h>
#include "Window.h"
#include "EventSystem/GlobalEventSystem.h"


Window::Window(float width, float height, const std::string& title) : width(width), height(height), title(title) {}

int Window::init() {
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

  glfwSetFramebufferSizeCallback(glfwWindow, [] (GLFWwindow* window, int width, int height) {
    auto* windowPointer = (Window*) glfwGetWindowUserPointer(window);

    windowPointer->width = width;
    windowPointer->width = height;

    auto messageData = EventSystem::MessageData{};
    messageData.f32[0] = width;
    messageData.f32[1] = height;
    eventSystem.messagePushOnQueue("windowResize", messageData);
  });

  glfwSetKeyCallback(glfwWindow, [] (GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto messageData = EventSystem::MessageData{};
    messageData.i32[0] = key;
    messageData.i32[1] = action;
    eventSystem.messagePushOnQueue("keyCallback", messageData);
  });

  glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow* window, double xpos, double ypos) {
    auto messageData = EventSystem::MessageData{};
    messageData.d64[0] = xpos;
    messageData.d64[1] = ypos;
    eventSystem.messagePushOnQueue("cursorPosCallback", messageData);
  });

  glfwSwapInterval(0);
  return 0;
}

bool Window::shouldClose() const {
  return glfwWindowShouldClose(glfwWindow);
};

void Window::swapBuffers() const {
  glfwSwapBuffers(glfwWindow);
}

void Window::pollEvents() {
  glfwPollEvents();
}

void Window::cleanup() const {
  glfwDestroyWindow(glfwWindow);
  glfwTerminate();
}
