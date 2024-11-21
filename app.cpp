#include "app.hpp"
#include <raylib.h>

App::App(int windowWidth, int windowHeight) {
  InitWindow(windowWidth,windowHeight, "Tetris");
  SetTargetFPS(60);

  const int width = 10;
  const int height = 20;
  char board[width][height];

  // Inialized board state
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      board[x][y] = 0;
    }
  }

  while(!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(Color{31,31,31,255});

      // Draw board
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          if (board[x][y] == 1) DrawRectangle(x*10,y*10,10,10,WHITE);
        }
      }
    EndDrawing();
  }
  CloseWindow();
}
