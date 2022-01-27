#include "cube.h"

std::vector<float> createCubeVertices(const TextureRectangle& textureRectangle, const TextureRectangle& top) {

  return {
    // Positions,                     Texture Coordinates

    // Front Face.
    0.0f, 1.0f, 0.0f,                 textureRectangle.x, textureRectangle.y, // 0
    0.0f, 0.0f, 0.0f,                 textureRectangle.x, textureRectangle.y - textureRectangle.height, // 1
    1.0f, 0.0f, 0.0f,                 textureRectangle.x + textureRectangle.width, textureRectangle.y - textureRectangle.height, // 2

    1.0f, 1.0f, 0.0f,                textureRectangle.x + textureRectangle.width, textureRectangle.y, // 3
    // 0
    // 2

    // Side Face(Visible)
    1.0f, 1.0f, 0.0f,                 textureRectangle.x, textureRectangle.y, // 4
    1.0f, 0.0f, 0.0f,                 textureRectangle.x, textureRectangle.y - textureRectangle.height, // 5
    1.0f, 1.0f, -1.0f,                textureRectangle.x + textureRectangle.width, textureRectangle.y, // 6

    // 6
    // 5
    1.0f, 0.0f, -1.0f,                 textureRectangle.x + textureRectangle.width, textureRectangle.y - textureRectangle.height, // 7

    // Top Face
    1.0f, 1.0f, -1.0f,                 top.x + top.width, top.y, // 8
    0.0f, 1.0f, 0.0f,                 top.x, top.y - top.height,  // 9
    1.0f, 1.0f, 0.0f,                 top.x + top.width, top.y - top.height,  // 10

    0.0f, 1.0f, -1.0f,                 top.x, top.y, // 11
    // 9
    // 8

    // Side Face (Not Visible)
    0.0f, 1.0f, 0.0f,                 textureRectangle.x, textureRectangle.y, // 12
    0.0f, 0.0f, 0.0f,                 textureRectangle.x, textureRectangle.y - textureRectangle.height, // 13
    0.0f, 1.0f, -1.0f,                textureRectangle.x + textureRectangle.width, textureRectangle.y, // 14

    // 14
    // 13
    0.0f, 0.0f, -1.0f,                 textureRectangle.x + textureRectangle.width, textureRectangle.y - textureRectangle.height, // 15

    // Back Face
    0.0f, 1.0f, -1.0f,                 textureRectangle.x, textureRectangle.y, // 16
    0.0f, 0.0f, -1.0f,                 textureRectangle.x, textureRectangle.y - textureRectangle.height, // 17
    1.0f, 0.0f, -1.0f,                 textureRectangle.x + textureRectangle.width, textureRectangle.y - textureRectangle.height, // 18

    1.0f, 1.0f, -1.0f,                 textureRectangle.x + textureRectangle.width, textureRectangle.y, // 19
    // 16
    // 18

    // Bottom Face
    0.0f, 0.0f, -1.0f,                  textureRectangle.x, textureRectangle.y, // 20
    0.0f, 0.0f, 0.0f,                   textureRectangle.x, textureRectangle.y - textureRectangle.height, // 21
    1.0f, 0.0f, 0.0f,                   textureRectangle.x + textureRectangle.width, textureRectangle.y - textureRectangle.height, // 22

    1.0f, 0.0f, -1.0f,                  textureRectangle.x + textureRectangle.width, textureRectangle.y, // 23
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

// p = position increment amount
std::vector<float> createCubeVertices(const glm::vec3& p, const TextureRectangle& textureRectangle, const TextureRectangle& top) {

  return {
    // Positions,                  Colors,                         Texture Coordinates

    // Front Face.
    0.0f + p.x, 1.0f + p.y, 0.0f + p.z,                 textureRectangle.x, textureRectangle.y, // 0
    0.0f + p.x, 0.0f + p.y, 0.0f + p.z,                 textureRectangle.x, textureRectangle.y - textureRectangle.height, // 1
    1.0f + p.x, 0.0f + p.y, 0.0f + p.z,                 textureRectangle.x + textureRectangle.width, textureRectangle.y - textureRectangle.height, // 2.x
    1.0f + p.x, 1.0f + p.y, 0.0f + p.z,                textureRectangle.x + textureRectangle.width, textureRectangle.y, // 3
    // 0
    // 2

    // Side Face(Visible)
    1.0f + p.x, 1.0f + p.y, 0.0f + p.z,                 textureRectangle.x, textureRectangle.y, // 4
    1.0f + p.x, 0.0f + p.y, 0.0f + p.z,                 textureRectangle.x, textureRectangle.y - textureRectangle.height, // 5
    1.0f + p.x, 1.0f + p.y, -1.0f + p.z,                textureRectangle.x + textureRectangle.width, textureRectangle.y, // 6

    // 6
    // 5
    1.0f + p.x, 0.0f + p.y, -1.0f + p.z,                 textureRectangle.x + textureRectangle.width, textureRectangle.y - textureRectangle.height, // 7

    // Top Face
    1.0f + p.x, 1.0f + p.y, -1.0f + p.z,                 top.x + top.width, top.y, // 8
    0.0f + p.x, 1.0f + p.y, 0.0f + p.z,                 top.x, top.y - top.height,  // 9
    1.0f + p.x, 1.0f + p.y, 0.0f + p.z,                 top.x + top.width, top.y - top.height,  // 10

    0.0f + p.x, 1.0f + p.y, -1.0f + p.z,                 top.x, top.y, // 11
    // 9
    // 8

    // Side Face (Not Visible)
    0.0f + p.x, 1.0f + p.y, 0.0f + p.z,                 textureRectangle.x, textureRectangle.y, // 12
    0.0f + p.x, 0.0f + p.y, 0.0f + p.z,                 textureRectangle.x, textureRectangle.y - textureRectangle.height, // 13
    0.0f + p.x, 1.0f + p.y, -1.0f + p.z,                textureRectangle.x + textureRectangle.width, textureRectangle.y, // 14

    // 14
    // 13
    0.0f + p.x, 0.0f + p.y, -1.0f + p.z,                 textureRectangle.x + textureRectangle.width, textureRectangle.y - textureRectangle.height, // 15

    // Back Face
    0.0f + p.x, 1.0f + p.y, -1.0f + p.z,                 textureRectangle.x, textureRectangle.y, // 16
    0.0f + p.x, 0.0f + p.y, -1.0f + p.z,                 textureRectangle.x, textureRectangle.y - textureRectangle.height, // 17
    1.0f + p.x, 0.0f + p.y, -1.0f + p.z,                 textureRectangle.x + textureRectangle.width, textureRectangle.y - textureRectangle.height, // 18
    1.0f + p.x, 1.0f + p.y, -1.0f + p.z,                 textureRectangle.x + textureRectangle.width, textureRectangle.y, // 19
    // 16
    // 18

    // Bottom Face
    0.0f + p.x, 0.0f + p.y, -1.0f + p.z,                  textureRectangle.x, textureRectangle.y, // 20
    0.0f + p.x, 0.0f + p.y, 0.0f + p.z,                   textureRectangle.x, textureRectangle.y - textureRectangle.height, // 21
    1.0f + p.x, 0.0f + p.y, 0.0f + p.z,                   textureRectangle.x + textureRectangle.width, textureRectangle.y - textureRectangle.height, // 22

    1.0f + p.x, 0.0f + p.y, -1.0f + p.z,                  textureRectangle.x + textureRectangle.width, textureRectangle.y, // 23
    // 20
    // 22
  };

}

std::vector<unsigned int> createCubeIndices(unsigned int i) {
  return {

    // Front Face
    0 + i, 1 + i, 2 + i,
    3 + i, 0 + i, 2 + i,
    // Side Face
    4 + i, 5 + i, 6 + i,
    6 + i, 5 + i, 7 + i,

    // Top Face
    8 + i, 9 + i, 10 + i,
    11 + i, 9 + i, 8 + i,

    // Side Face
    12 + i, 13 + i, 14 + i,
    14 + i, 13 + i, 15 + i,

    // Back Face
    16 + i, 17 + i, 18 + i,
    19 + i, 16 + i, 18 + i,

    // Bottom Face
    20 + i, 21 + i, 22 + i,
    23 + i, 20 + i, 22 + i

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
