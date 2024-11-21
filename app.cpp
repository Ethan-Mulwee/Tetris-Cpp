// STL
#include <iostream>
#include <chrono>

#include <raylib.h>

#include "app.hpp"
#include "tetrominos.hpp"

// Global vars
const Color colors[10] = {Color{0,0,0,0}, Color{255,255,255,255}};
const int width = 12;
const int height = 21;
char board[width][height];


// Tetromino functions

void RotateTetromino(Tetromino tetromino, int times) {

}

void DrawTetromino(Tetromino tetromino, int x, int y) {
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

// Check if tetromino its in board position
bool TetrominoFits(Tetromino tetromino, int x, int y) {
  bool result = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result = result && !(tetromino.shape[i][j] != 0 && board[i+x][j+y] != 0);
    }
  }
  return result;
}

// Add tetromino to board char array
void PlaceTetromino(Tetromino tetromino, int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetromino.shape[i][j] != 0) 
        board[i+x][j+y] = tetromino.shape[i][j];
    }
  }
}

App::App(int windowWidth, int windowHeight) {
  InitWindow(windowWidth,windowHeight, "Tetris");
  SetTargetFPS(60);

  Tetromino tetromino = tetrominos[0];

  int tetrominoX = 0;
  int tetrominoY = 0;

  // Timing
  std::chrono::steady_clock clock;
  auto lastFrameTime = clock.now();
  std::chrono::duration<double> deltaTickTime;
  std::chrono::duration<double> GameTimer;
  bool GameTick;


  // Inialized board state
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (y == height-1 || (x == 0 || x == width-1)) board[x][y] = 1;
      else board[x][y] = 0;
    }
  }

  // Game loop
  while(!WindowShouldClose()) {
    // TODO: cleanup timing code
    // Timing 
    auto currentFrameTime = clock.now();
    deltaTickTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
    GameTimer += deltaTickTime;
    if (GameTimer.count() > 1) {
      GameTick = true;
      GameTimer = std::chrono::duration<double>();
    }

    // Input
    if (IsKeyPressed(KEY_RIGHT))
      if (TetrominoFits(tetromino, tetrominoX+1, tetrominoY))
        tetrominoX += 1;
    if (IsKeyPressed(KEY_LEFT))
      if (TetrominoFits(tetromino, tetrominoX-1, tetrominoY))
        tetrominoX -= 1;

    // Logic
    if (GameTick) {
      if(TetrominoFits(tetromino, tetrominoX, tetrominoY+1)) {
        tetrominoY += 1;
      }
      else {
        PlaceTetromino(tetromino, tetrominoX, tetrominoY);
        tetrominoX = 0;
        tetrominoY = 0;
      }
      GameTick = false;
    }

    // Drawing
    BeginDrawing();
      ClearBackground(Color{31,31,31,255});

      // Draw board
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          DrawRectangle(x*10,y*10,10,10,colors[board[x][y]]);
        }
      }

      DrawTetromino(tetromino, tetrominoX, tetrominoY);

    EndDrawing();
  }
  CloseWindow();
}
