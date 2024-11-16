#include "app.hpp"
#include <raylib.h>

App::App(int windowWidth, int windowHeight, int boardWidth, int boardHeight) : board(boardWidth,boardHeight) {
  InitWindow(windowWidth,windowHeight, "Tetris");
  SetTargetFPS(60);

  while(!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(Color{31,31,31,255});
    EndDrawing();
  }
  CloseWindow();
}
