#include "precompiledheader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window/window.h"

#include "defer.h"
#include "Utils/ReadFile.h"

#include "renderer/renderer.h"
#include "renderer/mesh.h"
#include "renderer/ShaderProgram.h"
#include "editor_camera.h"
#include "renderer/primitives.h"
#include <glm/gtc/random.hpp>
#include <glm/gtc/noise.hpp>

enum struct Block_Type {
  Air,
  Dirt,
  Water
};

int main() {

  Window game_window{};
  game_window.init(1600, 900, "Minecraft");

  Renderer renderer;

  Mesh* voxels_geometry = new Mesh(Vertex_Layout{Vertex_Layout_Flag::XYZ_RGBA});
  constexpr int MAP_WIDTH = 200;
  constexpr int MAP_HEIGHT = 25;
  constexpr int MAP_Z = 200;
  static Block_Type blocks[MAP_WIDTH][MAP_HEIGHT][MAP_Z];

  // Generate Ground
  constexpr int GROUND_LEVEL = 5;
  for (int x = 0; x < MAP_WIDTH; ++x) {
    for (int y = 0; y < GROUND_LEVEL; ++y) {
      for (int z = 0; z < MAP_Z; ++z) {
        blocks[x][y][z] = Block_Type::Dirt;
      }
    }
  }

  // Generate Cliffs

  for (int x = 0; x < MAP_WIDTH; ++x) {
      for (int z = 0; z < MAP_Z; ++z) {
        float noise = 10 * (glm::perlin(glm::vec2{x * 0.05, z * 0.05}) + 1) / 2;

        for (int y = 0; y < noise; ++y) {
          blocks[x][y + GROUND_LEVEL][z] = Block_Type::Dirt;
        }

      }
  }

    


  // Generate Vertices from map data
  for (int x = 0; x < MAP_WIDTH; ++x) {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
      for (int z = 0; z < MAP_Z; ++z) {

        Block_Type current_block = blocks[x][y][z];
        if(current_block != Block_Type::Air) {
          float g = static_cast<float>(x) / static_cast<float>(MAP_WIDTH);
          float b = static_cast<float>(z) / static_cast<float>(MAP_Z);
          float n = (glm::simplex(glm::vec3{x * 0.5, y *.5, z * 0.5}) + 1) / 2;
          float n2 = (glm::simplex(glm::vec3{x * 0.05, y * .5, z * 0.05}) + 1) / 2;
          float n3 = (glm::simplex(glm::vec3{x * 0.01, y * .1, z * 0.15}) + 1) / 2;
          add_cube(*voxels_geometry, glm::vec3{x, y, z}, glm::vec4{n3, g * n, b * n2, 1});
        }

      }
    }
  }
  voxels_geometry->build();

  Model voxels{*voxels_geometry};
  voxels.set_material(renderer.default_material);


  Editor_Camera camera({0, 0, 3}, Projection_Data(1600.0f / 900));

  Shader_Program shader(readFile("assets/shaders/basic.vs"), readFile("assets/shaders/basic.fs"));
  glfwSetInputMode(game_window.get_window_handle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  float delta{};
  float last_frame{};
  while(!game_window.should_close()) {
    float now = glfwGetTime();
    delta = now - last_frame;
    last_frame = now;

    camera.process_input(delta);
    camera.process_mouse_input();
    if(Input::is_key_pressed(Key::KEY_ESCAPE)) break;

    glClearColor(123 / 255.0f, 165 / 255.0f, 232 / 255.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    shader.bind();
    shader.set_mat4("u_projection", camera.projection);
    shader.set_mat4("u_view", camera.view);
    auto identity = glm::mat4(1.0f);
    auto model = glm::mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.renderer_id, "u_model"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader.renderer_id, "u_animation_channel_1"), 1, GL_FALSE, &identity[0][0]);
    glUniform4fv(glGetUniformLocation(shader.renderer_id, "u_base_color"), 1, &renderer.default_material.color[0]);
    voxels.draw();

    game_window.poll_for_events();
    game_window.swap_buffers();
  }

}