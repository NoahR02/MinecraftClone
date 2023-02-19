#pragma once

#include "renderer.h"

void add_triangle(Model& model, const glm::vec3& position, const glm::vec4& color) {
  model.mesh.position({0, 5, 0})->color({255, 0, 0, 255});
  model.mesh.position({-5, 0, 0})->color({255, 0, 0, 255});
  model.mesh.position({5, 0, 0})->color({255, 0, 0, 255});
}

void add_cube(Mesh& mesh, const glm::vec3& position, const glm::vec4& color) {
  // Back Face (0 - 3)
  mesh.position({0.0f + position.x, 1.0f + position.y, 0.0f + position.z})->color(color);
  mesh.position({0.0f + position.x, 0.0f + position.y, 0.0f + position.z})->color(color);
  mesh.position({1.0f + position.x, 0.0f + position.y, 0.0f + position.z})->color(color);
  mesh.position({1.0f + position.x, 1.0f + position.y, 0.0f + position.z})->color(color);

  // Side Face (4 - 7)
  mesh.position({1.0f + position.x, 1.0f + position.y, 1.0f + position.z})->color(color); // 0
  mesh.position({1.0f + position.x, 0.0f + position.y, 1.0f + position.z})->color(color); // 1
  mesh.position({1.0f + position.x, 0.0f + position.y, 0.0f + position.z})->color(color); // 2
  mesh.position({1.0f + position.x, 1.0f + position.y, 0.0f + position.z})->color(color); // 3

  // Top Face (8 - 11)
  mesh.position({0.0f + position.x, 1.0f + position.y, 0.0f + position.z})->color(color);
  mesh.position({0.0f + position.x, 1.0f + position.y, 1.0f + position.z})->color(color);
  mesh.position({1.0f + position.x, 1.0f + position.y, 1.0f + position.z})->color(color);
  mesh.position({1.0f + position.x, 1.0f + position.y, 0.0f + position.z})->color(color);

  // Side Face (Not Visible) (12 - 15)
  mesh.position({0.0f + position.x, 1.0f + position.y, 0.0f + position.z})->color(color);
  mesh.position({0.0f + position.x, 1.0f + position.y, 1.0f + position.z})->color(color);
  mesh.position({0.0f + position.x, 0.0f + position.y, 1.0f + position.z})->color(color);
  mesh.position({0.0f + position.x, 0.0f + position.y, 0.0f + position.z})->color(color);

  // Front Face (16 - 19)
  mesh.position({ 0.0f + position.x, 1.0f + position.y, 1.0f + position.z})->color(color);
  mesh.position({ 0.0f + position.x, 0.0f + position.y, 1.0f + position.z})->color(color);
  mesh.position({ 1.0f + position.x, 0.0f + position.y, 1.0f + position.z})->color(color);
  mesh.position({ 1.0f + position.x, 1.0f + position.y, 1.0f + position.z})->color(color);

  // Bottom Face (20 - 23)
  mesh.position({ 0.0f + position.x, 0.0f + position.y, 0.0f + position.z})->color(color);
  mesh.position({ 0.0f + position.x, 0.0f + position.y, 1.0f + position.z})->color(color);
  mesh.position({ 1.0f + position.x, 0.0f + position.y, 1.0f + position.z})->color(color);
  mesh.position({ 1.0f + position.x, 0.0f + position.y, 0.0f + position.z})->color(color);

  const int current_cube_count = mesh.indices.size() / 36;
  const unsigned int next_start_index = 24 * current_cube_count;
  mesh.add_indices({
    // Back Face
    next_start_index + 0, next_start_index + 1, next_start_index + 2,
    next_start_index + 3, next_start_index + 0, next_start_index + 2,

    // Side Face
    next_start_index + 4, next_start_index + 5, next_start_index + 6,
    next_start_index + 7, next_start_index + 4, next_start_index + 6,

    // Top Face
    next_start_index + 8,  next_start_index + 9, next_start_index + 10,
    next_start_index + 11, next_start_index + 8, next_start_index + 10,

    // Side Face
    next_start_index + 12, next_start_index + 13, next_start_index + 14,
    next_start_index + 12, next_start_index + 14, next_start_index + 15,

    // Front Face
    next_start_index + 16, next_start_index + 17, next_start_index + 18,
    next_start_index + 19, next_start_index + 16, next_start_index + 18,

    // Bottom Face
    next_start_index + 20, next_start_index + 21, next_start_index + 22,
    next_start_index + 23, next_start_index + 20, next_start_index + 22
  });
}