#pragma once

#include <vector>
#include "Renderer/TextureRectangle.h"

constexpr unsigned int CUBE_INDICES_INCREMENT_AMOUNT = 24;

std::vector<float> createCubeVertices(const TextureRectangle& textureRectangle, const TextureRectangle& top);
std::vector<float> createCubeVertices(const glm::vec3& p, const TextureRectangle& textureRectangle, const TextureRectangle& top);
std::vector<unsigned int> createCubeIndices(unsigned int i);
std::vector<unsigned int> createCubeIndices();

TextureRectangle imageToNDC(int textureWidth, int textureHeight, int column, int row, float width, float height);
