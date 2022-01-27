#include "precompiledheader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/noise.hpp>

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

enum struct BlockType {
  Grass
};

std::unordered_map<BlockType, glm::vec2> textureCoordinates;

struct Block {
  BlockType blockType;
};

struct Chunk {

  glm::vec3 position;

  VertexArray vao;
  VertexBuffer vbo;
  IndexBuffer ibo;
  std::vector<float> vertices;
  std::vector<unsigned int> indices;

  explicit Chunk(const glm::vec3& position, const TextureRectangle& textureRectangle1, const TextureRectangle& textureRectangle2) : position(position) {

    vao.bind();
    vbo.bind();
    ibo.bind();

    float iIncrement = 0.0f;

    constexpr int SCALE = 16;

    for(int x = 0 + (int)position.x; x < 16 * SCALE + position.x; ++x) {
      for(int z = 0 + (int)position.z; z < 16 * SCALE + position.z; ++z) {

        float frequency = 200;
        auto result = pow((glm::simplex((glm::vec2{(float)x/ (frequency + (float)(rand() % 1)), (float)z/(float)(frequency + (rand() % 1))})) + 1) / 2 * 2, 8) / 12;
        frequency = 190;
        result += pow((glm::simplex((glm::vec2{(float)x/ (frequency + (float)(rand() % 1)), (float)z/(float)(frequency + (rand() % 1))})) + 1) / 2 * 2, 8) / 12;
        frequency = 210;
        result += pow((glm::simplex((glm::vec2{(float)x/ (frequency + (float)(rand() % 1)), (float)z/(float)(frequency + (rand() % 1))})) + 1) / 2 * 2, 8) / 12;
        frequency = 80;
        result += (glm::simplex((glm::vec2{(float)x/ (frequency + (float)(rand() % 1)), (float)z/(float)(frequency + (rand() % 1))})) + 1) / 2 * 5;
        frequency = 50;
        result += (glm::simplex((glm::vec2{(float)x/ (frequency + (float)(rand() % 1)), (float)z/(float)(frequency + (rand() % 1))})) + 1) / 2 * 2;
        frequency = 40;
        result += (glm::simplex((glm::vec2{(float)x/ (frequency + (float)(rand() % 1)), (float)z/(float)(frequency + (rand() % 1))})) + 1) / 2 * 15;
        frequency = 100;
        result += (glm::simplex((glm::vec2{(float)x/ (frequency + (float)(rand() % 1)), (float)z/(float)(frequency + (rand() % 1))})) + 1) / 2 * 10;
        frequency = 200;
        result += (glm::simplex((glm::vec2{(float)x/ (frequency + (float)(rand() % 1)), (float)z/(float)(frequency + (rand() % 1))})) + 1) / 2 * 5;


        for(int y = -10; y < 0; ++y) {
          const std::vector tmpV = createCubeVertices({(float)x, (float)y, (float)z},textureRectangle1, textureRectangle2);
          vertices.insert(vertices.end(), tmpV.begin(), tmpV.end());

          const std::vector tmpI = createCubeIndices(iIncrement);
          indices.insert(indices.end(), tmpI.begin(), tmpI.end());

          iIncrement += CUBE_INDICES_INCREMENT_AMOUNT;
        }

        for(int y = 0; y < result; ++y) {
          const std::vector tmpV = createCubeVertices({(float)x, (float)y, (float)z},textureRectangle1, textureRectangle2);
          vertices.insert(vertices.end(), tmpV.begin(), tmpV.end());

          const std::vector tmpI = createCubeIndices(iIncrement);
          indices.insert(indices.end(), tmpI.begin(), tmpI.end());

          iIncrement += CUBE_INDICES_INCREMENT_AMOUNT;
        }
      }
    }

    vbo.uploadBufferData(vertices, GL_DYNAMIC_DRAW);
    ibo.uploadBufferData(indices, GL_DYNAMIC_DRAW);

    vao.enableAttribute(0);
    vao.describeAttributeLayout(0, 3, GL_FLOAT, false, sizeof(float) * 5, 0);

    vao.enableAttribute(1);
    vao.describeAttributeLayout(1, 2, GL_FLOAT, false, sizeof(float) * 5, (sizeof(float) * 3));
  }

  void render(ShaderProgram& shaderProgram, Texture& texture) {
    shaderProgram.bind();
    texture.bind();

    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
  }


};

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
  cubeVAO.describeAttributeLayout(0, 3, GL_FLOAT, false, sizeof(float) * 5, 0);

  cubeVAO.enableAttribute(1);
  cubeVAO.describeAttributeLayout(1, 2, GL_FLOAT, false, sizeof(float) * 5, (sizeof(float) * 3));

  glEnable(GL_DEPTH_TEST);

  float lastFrame = 0.0f;
  float deltaTime;

  glfwSetCursorPos(window.glfwWindow, 1600 / 2, 900 / 2);

  Camera camera(window.width, window.height, {0.0f, 10.0f, 3.0f});

  constexpr float fov = 45.0f;
  constexpr float nearPlane = 0.1f;
  constexpr float farPlane = 500.0f;

  Chunk chunk({-20, 0, -20}, sidesOfGrassInfo, topOfGrassInfo);

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

    chunk.render(program, texture);

    window.pollEvents();
    window.swapBuffers();
  }

}