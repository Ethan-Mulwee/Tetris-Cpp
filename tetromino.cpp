#include <raylib.h>

#include "tetromino.hpp"

void Tetromino::Draw(int x, int y, int scale, Color *colors) {
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      DrawRectangle(x,y,scale,scale,colors[shape[i][j]]);
      DrawRectangle(x+2,y+2,scale-4,scale-4,ColorBrightness(colors[shape[i][j]],-0.1f));
    }
  }
}

void Tetromino::Rotate(int r) {
  Tetromino result;
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      // transposes for the moment
      result.shape[i][j] = shape[j][3-i];
    }
  }
  *this = result;
}

Tetromino Tetromino::Rotated(int r)
{
  Tetromino result;
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      // transposes for the moment
      result.shape[i][j] = shape[j][3-i];
    }
  }
  return result;
}