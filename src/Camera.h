#pragma once

/*
 * TODO:
 * Research the math behind the camera code and make it smoother.
 */

/**
 *
 * Almost all of the camera code is from this youtube tutorial:
 * https://www.youtube.com/watch?v=86_pQCKOIPk
 *
 */

#include "Renderer/ShaderProgram.h"
#include "Input.h"
#include "Window.h"

struct Camera {

  glm::vec3 position;
  glm::vec3 direction = {0.0f, 0.0f, -1.0f};
  glm::vec3 up = {0.0f, 1.0f, 0.0f};

  int width;
  int height;

  bool firstClick = true;

  float speed = 4.00f;
  float sensitivity = 100.0f;

  Camera(int width, int height, const glm::vec3& position);

  void uploadMatrixToShader(float fov, float nearPlane, float farPlane, const ShaderProgram& shader);
  void handleCameraInput(Window& window, const Input& input, float deltaTime);

};