#include "Camera.h"
#include "GLFW/glfw3.h"

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

Camera::Camera(int width, int height, const glm::vec3 &position) : width(width), height(height), position(position) {}

void Camera::uploadMatrixToShader(float fov, float nearPlane, float farPlane, const ShaderProgram &shader) {

  glm::mat4 view{1.0f};
  glm::mat4 projection{1.0f};

  view = glm::lookAt(position, position + direction, up);
  projection = glm::perspective(fov, (float)width / height, nearPlane, farPlane);

  shader.uniformMatrix4fv("uMVP", 1, false, glm::value_ptr(projection * view));

}

void Camera::handleCameraInput(Window& window, const Input& input, float deltaTime) {

   if(input.keys[GLFW_KEY_W]) {
     position += speed * direction * deltaTime;
   }

   if(input.keys[GLFW_KEY_A]) {
     position += speed * -glm::normalize(glm::cross(direction, up)) * deltaTime;
   }

   if(input.keys[GLFW_KEY_S]) {
     position += speed * -direction * deltaTime;
   }

   if(input.keys[GLFW_KEY_D]) {
     position += speed * glm::normalize(glm::cross(direction, up)) * deltaTime;
   }

  if(input.keys[GLFW_KEY_SPACE]) {
    position += speed * up * deltaTime;
  }

  if(input.keys[GLFW_KEY_LEFT_CONTROL]) {
    position += speed * -up * deltaTime;
  }

  if(glfwGetMouseButton(window.glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    glfwSetInputMode(window.glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if(firstClick) {
      glfwSetCursorPos(window.glfwWindow, (width / 2), (height / 2));
      firstClick = false;
    }

    double mouseX;
    double mouseY;

    glfwGetCursorPos(window.glfwWindow, &mouseX, &mouseY);

    float rotationX = sensitivity *  (float)(mouseY - (height / 2)) / height;
    float rotationY = sensitivity *  (float)(mouseX - (width / 2)) / width;

    glm::vec3 direction = glm::rotate(this->direction, glm::radians(-rotationX), glm::normalize(glm::normalize(glm::cross(this->direction, up))));

    if(glm::abs(glm::angle(this->direction, up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
      this->direction = direction;
    }

    this->direction = glm::rotate(this->direction, glm::radians(-rotationY), up);
    glfwSetCursorPos(window.glfwWindow, (width / 2), (height / 2));
  }

  if(glfwGetMouseButton(window.glfwWindow, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS) {
    glfwSetInputMode(window.glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    firstClick = true;
  }

}
