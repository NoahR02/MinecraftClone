#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <utility>

#include "mesh.h"
#include "model.h"

class Renderer {

public:
  Material default_material{};

  Renderer() {
    glGenTextures(1, reinterpret_cast<GLuint *>(&default_material.base_color_texture_handle));
    glBindTexture(GL_TEXTURE_2D, default_material.base_color_texture_handle);
    glActiveTexture(0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char white_texture[4] = {255, 255, 255, 255};

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &white_texture[0]);
  }
};