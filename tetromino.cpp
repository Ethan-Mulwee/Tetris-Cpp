#include "tetromino.hpp"

Tetromino Tetromino::Rotated(int r) {
  Tetromino result;
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      // transposes for the moment
      result.shape[i][j] = shape[j][3-i];
    }
  }
  return result;
}