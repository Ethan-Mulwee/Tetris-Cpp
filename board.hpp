#ifndef TETRIS_BOARD
#define TETRIS_BOARD

#include "tetromino.hpp"

struct Board {
  const static int width = 12;
  const static int height = 21;
  char data[width][height];

  Board();

  // Draw board
  void Draw(int x, int y, int scale, Color* colors);

  // Add tetromino to board char array
  void Add(Tetromino tetromino, int x, int y);

  // Clear line and move down everything above it
  void ClearLine(int clearedY);

  // Checks if line is filled
  bool CheckLine(int y);

  // Check if given tetromino fits at cords x and y
  bool Fits(Tetromino tetromino, int x, int y);
};

#endif