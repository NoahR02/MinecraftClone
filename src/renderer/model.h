#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <utility>
#include "renderer.h"

struct Material {
  glm::vec4 color = {255.0f, 255.0f, 255.0f, 255.0f};
  unsigned int base_color_texture_handle{};

  Material() {

  }

};

class Model {
  Material material;
public:
  explicit Model(Mesh& mesh) : mesh(std::move(mesh)) { }

  void draw() {
    glBindTexture(GL_TEXTURE_2D, material.base_color_texture_handle);
    glActiveTexture(0);
    glBindVertexArray(mesh.vao);

    if(mesh.has_indices()) {
      glDrawElements(GL_TRIANGLES, mesh.index_count, GL_UNSIGNED_INT, nullptr);
      return;
    }

    glDrawArrays(GL_TRIANGLES, 0, mesh.vertex_count);
  }

public:
  Mesh mesh;

  void set_material(Material material) {
    this->material = material;
  }
};