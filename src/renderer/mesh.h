#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <utility>

struct Attribute_Layout {
  int component_count{}; // Vec2 = 2, Vec3 = 3. Max = 4
  // Offset relative to the start of the vertex.
  int offset{};
};

enum struct Vertex_Layout_Flag {
  Custom,
  XYZ,
  XYZ_RGBA,
};

struct Vertex_Layout {

  explicit Vertex_Layout(Vertex_Layout_Flag vertex_layout_flag) {
    this->vertex_layout_flag = vertex_layout_flag;

    switch (vertex_layout_flag) {
      case Vertex_Layout_Flag::Custom: { break; }

      case Vertex_Layout_Flag::XYZ: {
        Attribute_Layout vertex_position{};
        vertex_position.component_count = 3;

        attributes.insert(attributes.end(), {vertex_position});
        break;
      }

      case Vertex_Layout_Flag::XYZ_RGBA: {
        Attribute_Layout vertex_position{};
        vertex_position.component_count = 3;

        Attribute_Layout vertex_color{};
        vertex_color.component_count = 4;
        vertex_color.offset = sizeof(float) * vertex_position.component_count;

        attributes.insert(attributes.end(), {vertex_position, vertex_color});
        break;
      }

      default: {
        std::unreachable();
      }

    }
  }

  explicit Vertex_Layout(const std::vector<Attribute_Layout>& attribute_layouts) {
    vertex_layout_flag = Vertex_Layout_Flag::Custom;
  }

  std::vector<Attribute_Layout> attributes{};
  Vertex_Layout_Flag vertex_layout_flag{};
};

class Mesh {

private:
  unsigned int vao{0};
  unsigned int vbo{0};
  unsigned int ibo{0};

  std::vector<float> vertices{};
  int index_count = 0;
  int vertex_count = 0;

  Vertex_Layout vertex_layout = Vertex_Layout(Vertex_Layout_Flag::Custom);

public:

  explicit Mesh(const Vertex_Layout& vertex_layout) {
    this->vertex_layout = vertex_layout;
    vertices.reserve(1610612736/8);
  }

  // XYZ
  Mesh* position(const glm::vec3& xyz) {
    vertices.insert(vertices.end(), {xyz.x, xyz.y, xyz.z});
    return this;
  }

  // RGBA
  Mesh* color(const glm::vec4& color) {
    vertices.insert(vertices.end(), {color.r, color.g, color.b, color.a});
    return this;
  }

  void add_indices(const std::vector<unsigned int>& indices) {
    this->indices.insert(this->indices.end(), indices.begin(), indices.end());
  }

  bool has_indices() const {
    return index_count;
  }

  bool has_vertices() const {
    return vertex_count;
  }

  void build() {
    if(vertices.empty()) {
      return;
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    index_count = indices.size();
    int total_components_across_attributes = 0;
    for(const auto& vertex_attribute : vertex_layout.attributes) {
      total_components_across_attributes += vertex_attribute.component_count;
    }
    if(total_components_across_attributes > 0) {
      vertex_count = vertices.size() / total_components_across_attributes;
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);


    if(has_indices()) {
      glGenBuffers(1, &ibo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
    }

    for(int i = 0; i < vertex_layout.attributes.size(); ++i) {
      const auto& current_attribute = vertex_layout.attributes[i];
      glEnableVertexAttribArray(i);
      glVertexAttribPointer(i, current_attribute.component_count, GL_FLOAT, false, sizeof(float) * total_components_across_attributes, (void*)current_attribute.offset);
    }

  }

  friend class Model;

  std::vector<unsigned int> indices{};
};