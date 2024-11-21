#include <iostream>
#include <raylib.h>

#include "app.hpp"
#include "tetrominos.hpp"


const Color colors[10] = {Color{0,0,0,0}, Color{255,255,255,255}};

void DrawTetromino(Tetromino tetromino, int x, int y) {
  // Temp draw tetromino
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      DrawRectangle((i+x)*10,(j+y)*10,10,10,colors[tetrominos[0].shape[i][j]]);
    }
  }
}

void PrintTetromino(Tetromino tetromino) {
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      std::cout << (int)tetrominos[0].shape[i][j];
    }
    std::cout << "\n";
  }
}

App::App(int windowWidth, int windowHeight) {
  InitWindow(windowWidth,windowHeight, "Tetris");
  SetTargetFPS(60);

  const int width = 12;
  const int height = 21;
  char board[width][height];


  // Inialized board state
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (y == height-1 || (x == 0 || x == width-1)) board[x][y] = 1;
      else board[x][y] = 0;
    }
  }


  while(!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(Color{31,31,31,255});

      // Draw board
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          DrawRectangle(x*10,y*10,10,10,colors[board[x][y]]);
        }
      }

      DrawTetromino(tetrominos[0], 4, 4);

    EndDrawing();
  }
  CloseWindow();
}
