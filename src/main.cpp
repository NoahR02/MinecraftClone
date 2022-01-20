#include "precompiledheader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Texture.h"
#include "Renderer/ShaderProgram.h"
#include "Renderer/TextureRectangle.h"
#include "Window.h"
#include "Input.h"

#include "EventSystem/GlobalEventSystem.h"
#include "defer.h"

#include "Camera.h"
#include "cube.h"
#include "Utils/ReadFile.h"

EventSystem eventSystem;
static Input input;

int main() {

  Window window(1600, 900, "MinecraftClone");

  if(window.init() == -1) {
    return -1;
  }

  defer(window.cleanup());

  glfwSetWindowUserPointer(window.glfwWindow, &window);
  glfwSetInputMode(window.glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  eventSystem.messageSubscribe("windowResize" , [](EventSystem::MessageData& messageData) {
    std::cout << "Window Width: " << messageData.f32[0] << std::endl;
    std::cout << "Window Height: " << messageData.f32[1] << std::endl;
  });

  eventSystem.messageSubscribe("keyCallback" , [  ](EventSystem::MessageData& messageData) {
    input.keys[messageData.i32[0]] = messageData.i32[1];
  });

  eventSystem.messageSubscribe("cursorPosCallback" , [](EventSystem::MessageData& messageData) {
    input.cursorXPosition = messageData.d64[0];
    input.cursorYPosition = messageData.d64[1];
  });

  const std::string vertexShaderString = readFile("assets/shaders/default.vert");
  const std::string fragmentShaderString = readFile("assets/shaders/default.frag");

  ShaderProgram program(vertexShaderString, fragmentShaderString);

  VertexBuffer cubeVBO;
  IndexBuffer cubeIBO;
  VertexArray cubeVAO;

  Texture texture("assets/textures/spritesheet.png");

  TextureRectangle sidesOfGrassInfo = imageToNDC(texture.width, texture.height, 0, 0, 16, 16);
  TextureRectangle topOfGrassInfo = imageToNDC(texture.width, texture.height, 1, 0, 16, 16);

  std::vector<float> cube = createCubeVertices(sidesOfGrassInfo, topOfGrassInfo);
  std::vector<unsigned int> cubeIndices = createCubeIndices();

  cubeVAO.bind();
  cubeVBO.bind();
  cubeIBO.bind();
  cubeVBO.uploadBufferData(cube, GL_STATIC_DRAW);
  cubeIBO.uploadBufferData(cubeIndices, GL_STATIC_DRAW);

  cubeVAO.enableAttribute(0);
  cubeVAO.describeAttributeLayout(0, 3, GL_FLOAT, false, sizeof(float) * 9, 0);

  cubeVAO.enableAttribute(1);
  cubeVAO.describeAttributeLayout(1, 4, GL_FLOAT, false, sizeof(float) * 9, (sizeof(float) * 3));

  cubeVAO.enableAttribute(2);
  cubeVAO.describeAttributeLayout(2, 2, GL_FLOAT, false, sizeof(float) * 9, (sizeof(float) * 7));

  glEnable(GL_DEPTH_TEST);

  float lastFrame = 0.0f;
  float deltaTime;

  glfwSetCursorPos(window.glfwWindow, 1600 / 2, 900 / 2);

  Camera camera(window.width, window.height, {0.0f, 0.0f, 3.0f});

  constexpr float fov = 45.0f;
  constexpr float nearPlane = 0.1f;
  constexpr float farPlane = 100.0f;

  while(!window.shouldClose()) {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;

    eventSystem.messageQueueExecuteAll();

    camera.handleCameraInput(window, input, deltaTime);

    glClearColor(123 / 255.0f, 165 / 255.0f, 232 / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.bind();
    texture.bind();


    cubeVAO.bind();
    program.uniform1i("texture", 0);
    camera.uploadMatrixToShader(fov, nearPlane, farPlane, program);
    glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, nullptr);


    window.pollEvents();
    window.swapBuffers();
  }

}