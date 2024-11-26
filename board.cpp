#include "board.hpp"

void Board::Add(Tetromino tetromino, int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetromino.shape[i][j] != 0) 
        data[i+x][j+y] = tetromino.shape[i][j];
    }
  }
}

bool Board::CheckLine(int y) {
  bool lineFilled = true;
  for (int x = 1; x < width-1; x++) {
    lineFilled = lineFilled && (data[x][y] != 0);
  }
  return lineFilled;
}

void Board::ClearLine(int clearedY) {
  for (int x = 1; x < width-1; x++) {
    data[x][clearedY] = 0;
    for (int y = clearedY-1; y >= 0; y--) {
      data[x][y+1] = data[x][y];
      data[x][y] = 0;
    }
  }
}

// Check if tetromino its in board position
bool Board::Fits(Tetromino tetromino, int x, int y) {
  bool result = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result = result && !(tetromino.shape[i][j] != 0 && data[i+x][j+y] != 0);
    }
  }
  return result;
}
