#include "precompiledheader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Texture.h"
#include "Renderer/ShaderProgram.h"
#include "Window.h"
#include "Input.h"

#include "EventSystem/GlobalEventSystem.h"
#include "defer.h"

#include "Camera.h"

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
                                       fragColor = texture(uTexture, outTextureCoordinates);
                                     })Shader";

  ShaderProgram program(vertexShaderString, fragmentShaderString);

  VertexBuffer cubeVBO;
  IndexBuffer cubeIBO;
  VertexArray cubeVAO;

  Texture texture("assets/textures/spritesheet.png");

  struct TextureRectangle {
    float x;
    float y;

    float width;
    float height;
  };

  auto imageToNDC = [] (int textureWidth, int textureHeight, int column, int row, float width, float height) -> TextureRectangle {

    return TextureRectangle {
      (column * width) / textureWidth,
      (row * height) / textureHeight,
      width / textureWidth,
      height / textureHeight
    };

  };

  TextureRectangle sidesOfGrassInfo = imageToNDC(texture.width, texture.height, 0, 0, 16, 16);
  TextureRectangle topOfGrassInfo = imageToNDC(texture.width, texture.height, 1, 0, 16, 16);

  std::vector<unsigned int> cubeIndices = {

    // Front Face
    0, 1, 2,
    3, 0, 2,
    // Side Face
    4, 5, 6,
    6, 5, 7,

    // Top Face
    8, 9, 10,
    11, 9, 8,

    // Side Face
    12, 13, 14,
    14, 13, 15,

    // Back Face
    16, 17, 18,
    19, 16, 18,

    // Bottom Face
    20, 21, 22,
    23, 20, 22

  };

  std::vector<float> cube = {


    // Positions,                  Colors,                         Texture Coordinates

    // Front Face.
    0.0f, 1.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          sidesOfGrassInfo.x, sidesOfGrassInfo.y, // 0
    0.0f, 0.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          sidesOfGrassInfo.x, sidesOfGrassInfo.y - sidesOfGrassInfo.height, // 1
    1.0f, 0.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          sidesOfGrassInfo.x + sidesOfGrassInfo.width, sidesOfGrassInfo.y - sidesOfGrassInfo.height, // 2

    1.0f, 1.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,         sidesOfGrassInfo.x + sidesOfGrassInfo.width, sidesOfGrassInfo.y, // 3
    // 0
    // 2

    // Side Face(Visible)
    1.0f, 1.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          sidesOfGrassInfo.x, sidesOfGrassInfo.y, // 4
    1.0f, 0.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          sidesOfGrassInfo.x, sidesOfGrassInfo.y - sidesOfGrassInfo.height, // 5
    1.0f, 1.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,         sidesOfGrassInfo.x + sidesOfGrassInfo.width, sidesOfGrassInfo.y, // 6

    // 6
    // 5
    1.0f, 0.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          sidesOfGrassInfo.x + sidesOfGrassInfo.width, sidesOfGrassInfo.y - sidesOfGrassInfo.height, // 7

    // Top Face
    1.0f, 1.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          topOfGrassInfo.x + topOfGrassInfo.width, topOfGrassInfo.y, // 8
    0.0f, 1.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          topOfGrassInfo.x, topOfGrassInfo.y - topOfGrassInfo.height,  // 9
    1.0f, 1.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          topOfGrassInfo.x + topOfGrassInfo.width, topOfGrassInfo.y - topOfGrassInfo.height,  // 10

    0.0f, 1.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          topOfGrassInfo.x, topOfGrassInfo.y, // 11
    // 9
    // 8

    // Side Face (Not Visible)
    0.0f, 1.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          sidesOfGrassInfo.x, sidesOfGrassInfo.y, // 12
    0.0f, 0.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          sidesOfGrassInfo.x, sidesOfGrassInfo.y - sidesOfGrassInfo.height, // 13
    0.0f, 1.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,         sidesOfGrassInfo.x + sidesOfGrassInfo.width, sidesOfGrassInfo.y, // 14

    // 14
    // 13
    0.0f, 0.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          sidesOfGrassInfo.x + sidesOfGrassInfo.width, sidesOfGrassInfo.y - sidesOfGrassInfo.height, // 15

    // Back Face
    0.0f, 1.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          sidesOfGrassInfo.x, sidesOfGrassInfo.y, // 16
    0.0f, 0.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          sidesOfGrassInfo.x, sidesOfGrassInfo.y - sidesOfGrassInfo.height, // 17
    1.0f, 0.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          sidesOfGrassInfo.x + sidesOfGrassInfo.width, sidesOfGrassInfo.y - sidesOfGrassInfo.height, // 18

    1.0f, 1.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          sidesOfGrassInfo.x + sidesOfGrassInfo.width, sidesOfGrassInfo.y, // 19
    // 16
    // 18

    // Bottom Face
    0.0f, 0.0f, -1.0f,              0.0f, 1.0f, 0.0f, 0.0f,          sidesOfGrassInfo.x, sidesOfGrassInfo.y, // 20
    0.0f, 0.0f, 0.0f,              0.0f, 1.0f, 0.0f, 0.0f,           sidesOfGrassInfo.x, sidesOfGrassInfo.y - sidesOfGrassInfo.height, // 21
    1.0f, 0.0f, 0.0f,              0.0f, 1.0f, 0.0f, 0.0f,           sidesOfGrassInfo.x + sidesOfGrassInfo.width, sidesOfGrassInfo.y - sidesOfGrassInfo.height, // 22

    1.0f, 0.0f, -1.0f,              0.0f, 1.0f, 0.0f, 0.0f,          sidesOfGrassInfo.x + sidesOfGrassInfo.width, sidesOfGrassInfo.y, // 23
    // 20
    // 22

  };


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

  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

  model = glm::scale(model, glm::vec3{0.5f, 0.5f, 0.5f});
  model = glm::translate(model, glm::vec3{-2.0f, -1.0f, 0.0f});

  glEnable(GL_DEPTH_TEST);

  float lastFrame = 0.0f;
  float deltaTime;

  glfwSetCursorPos(window.glfwWindow, 1600/2, 900/2);

  Camera camera(window.width, window.height, {0.0f, 0.0f, 3.0f});

  while(!window.shouldClose()) {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrame;
    lastFrame = currentTime;

    eventSystem.messageQueueExecuteAll();

    camera.handleCameraInput(window, input, deltaTime);
   /* if(input.keys[GLFW_KEY_W]) {
      cameraPosition += cameraFront * cameraSpeed;
    } else if(input.keys[GLFW_KEY_A]) {
      cameraPosition += -cameraRight * cameraSpeed;
    } else if(input.keys[GLFW_KEY_S]) {
      cameraPosition -= cameraFront * cameraSpeed;
    } else if(input.keys[GLFW_KEY_D]) {
      cameraPosition += cameraRight * cameraSpeed;
    }*/

    glClearColor(123/255.0f, 165/255.0f, 232/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.bind();
    texture.bind();


    cubeVAO.bind();
    program.uniform1i("texture", 0);
    camera.uploadMatrixToShader(45.0f, 0.1f, 100.0f, program);
    glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, nullptr);


    window.pollEvents();
    window.swapBuffers();
  }

}