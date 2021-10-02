#ifndef MINECRAFTCLONE_INPUT_H
#define MINECRAFTCLONE_INPUT_H

#include <cstdint>

#define KEY_UNKNOWN -1
#define KEY_RELEASED 0
#define KEY_PRESSED 1
#define KEY_REPEATED 2

#define MOUSE_RELEASED 0
#define MOUSE_PRESSED 1

struct Input {

  int16_t keys[400] {0};
  int8_t mouseButtons[20] {0};

  double cursorXPosition = NULL;
  double cursorYPosition = NULL;

  double lastCursorXPosition = NULL;
  double lastCursorYPosition = NULL;
};

#endif
