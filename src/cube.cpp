#include "cube.h"

std::vector<float> createCubeVertices(const TextureRectangle& textureRectangle, const TextureRectangle top) {

  return {
    // Positions,                  Colors,                         Texture Coordinates

    // Front Face.
    0.0f, 1.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          textureRectangle.x, textureRectangle.y, // 0
    0.0f, 0.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          textureRectangle.x, textureRectangle.y - textureRectangle.height, // 1
    1.0f, 0.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          textureRectangle.x + textureRectangle.width, textureRectangle.y - textureRectangle.height, // 2

    1.0f, 1.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,         textureRectangle.x + textureRectangle.width, textureRectangle.y, // 3
    // 0
    // 2

    // Side Face(Visible)
    1.0f, 1.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          textureRectangle.x, textureRectangle.y, // 4
    1.0f, 0.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          textureRectangle.x, textureRectangle.y - textureRectangle.height, // 5
    1.0f, 1.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,         textureRectangle.x + textureRectangle.width, textureRectangle.y, // 6

    // 6
    // 5
    1.0f, 0.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          textureRectangle.x + textureRectangle.width, textureRectangle.y - textureRectangle.height, // 7

    // Top Face
    1.0f, 1.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          top.x + top.width, top.y, // 8
    0.0f, 1.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          top.x, top.y - top.height,  // 9
    1.0f, 1.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          top.x + top.width, top.y - top.height,  // 10

    0.0f, 1.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          top.x, top.y, // 11
    // 9
    // 8

    // Side Face (Not Visible)
    0.0f, 1.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          textureRectangle.x, textureRectangle.y, // 12
    0.0f, 0.0f, 0.0f,             0.0f, 1.0f, 0.0f, 0.0f,          textureRectangle.x, textureRectangle.y - textureRectangle.height, // 13
    0.0f, 1.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,         textureRectangle.x + textureRectangle.width, textureRectangle.y, // 14

    // 14
    // 13
    0.0f, 0.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          textureRectangle.x + textureRectangle.width, textureRectangle.y - textureRectangle.height, // 15

    // Back Face
    0.0f, 1.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          textureRectangle.x, textureRectangle.y, // 16
    0.0f, 0.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          textureRectangle.x, textureRectangle.y - textureRectangle.height, // 17
    1.0f, 0.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          textureRectangle.x + textureRectangle.width, textureRectangle.y - textureRectangle.height, // 18

    1.0f, 1.0f, -1.0f,             0.0f, 1.0f, 0.0f, 0.0f,          textureRectangle.x + textureRectangle.width, textureRectangle.y, // 19
    // 16
    // 18

    // Bottom Face
    0.0f, 0.0f, -1.0f,              0.0f, 1.0f, 0.0f, 0.0f,          textureRectangle.x, textureRectangle.y, // 20
    0.0f, 0.0f, 0.0f,              0.0f, 1.0f, 0.0f, 0.0f,           textureRectangle.x, textureRectangle.y - textureRectangle.height, // 21
    1.0f, 0.0f, 0.0f,              0.0f, 1.0f, 0.0f, 0.0f,           textureRectangle.x + textureRectangle.width, textureRectangle.y - textureRectangle.height, // 22

    1.0f, 0.0f, -1.0f,              0.0f, 1.0f, 0.0f, 0.0f,          textureRectangle.x + textureRectangle.width, textureRectangle.y, // 23
    // 20
    // 22
  };

}

std::vector<unsigned int> createCubeIndices() {
 return {

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
}

TextureRectangle imageToNDC(int textureWidth, int textureHeight, int column, int row, float width, float height){

  return TextureRectangle {
    (column * width) / textureWidth,
    (row * height) / textureHeight,
    width / textureWidth,
    height / textureHeight
  };

}
