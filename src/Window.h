#ifndef MINECRAFTCLONE_WINDOW_H
#define MINECRAFTCLONE_WINDOW_H


#include <string>
#include <GLFW/glfw3.h>

struct Window {

  Window(const Window &) = delete;

  GLFWwindow* glfwWindow;
  float width;
  float height;
  std::string title;

  Window(float width, float height, const std::string& title);

  int init();

  bool shouldClose() const;
  void swapBuffers() const;
  void pollEvents();

  void cleanup() const;

private:
  Window() = delete;

};


#endif
