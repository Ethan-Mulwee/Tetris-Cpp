#include "app.hpp"
#include <raylib.h>

App::App(int windowWidth, int windowHeight, const int boardWidth, const int boardHeight) {
  InitWindow(windowWidth,windowHeight, "Tetris");
  SetTargetFPS(60);

  Board<boardWidth, boardHeight> board;

  while(!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(Color{31,31,31,255});
      for (int y = 0; y < boardHeight; y++) {
        for (int x = 0; x < boardWidth; x++) {
          if (board(x,y).state) DrawRectangle(x*10,y*10,10,10,WHITE);
        }
      }
    EndDrawing();
  }
  CloseWindow();
}
