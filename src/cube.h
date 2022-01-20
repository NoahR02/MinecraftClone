#pragma once

#include <vector>
#include "Renderer/TextureRectangle.h"

std::vector<float> createCubeVertices(const TextureRectangle& textureRectangle, const TextureRectangle top);
std::vector<unsigned int> createCubeIndices();

TextureRectangle imageToNDC(int textureWidth, int textureHeight, int column, int row, float width, float height);
