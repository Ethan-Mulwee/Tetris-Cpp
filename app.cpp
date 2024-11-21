// STL
#include <iostream>
#include <chrono>

#include <raylib.h>

#include "app.hpp"
#include "tetrominos.hpp"

// Global vars
const Color colors[10] = {Color{0,0,0,0}, LIGHTGRAY, YELLOW, BLUE, RED, GREEN, ORANGE, PINK, PURPLE};
const int width = 12;
const int height = 21;
char board[width][height];
const int renderScale = 20;


// Tetromino functions

// Returns tetromino rotated
Tetromino RotateTetromino(Tetromino tetromino, int times) {
  Tetromino result;
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      // transposes for the moment
      result.shape[i][j] = tetromino.shape[j][3-i];
    }
  }
  return result;
}

void DrawTetromino(Tetromino tetromino, int x, int y) {
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      DrawRectangle((i+x)*renderScale,(j+y)*renderScale,renderScale,renderScale,colors[tetromino.shape[i][j]]);
    }
  }
}

void PrintTetromino(Tetromino tetromino) {
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      std::cout << (int)tetromino.shape[i][j];
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

  Tetromino tetromino = tetrominos[GetRandomValue(0,6)];
  PrintTetromino(tetromino);

  int tetrominoX = 6;
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
    if (IsKeyPressed(KEY_DOWN))
      if (TetrominoFits(tetromino, tetrominoX, tetrominoY+1))
        tetrominoY += 1;
    if (IsKeyPressed(KEY_UP)) {
      Tetromino rotatedTetromino = RotateTetromino(tetromino, 1);
      if (TetrominoFits(rotatedTetromino, tetrominoX, tetrominoY))
        tetromino = rotatedTetromino;
    }

    // Logic
    if (GameTick) {
      if(TetrominoFits(tetromino, tetrominoX, tetrominoY+1)) {
        tetrominoY += 1;
      }
      else {
        PlaceTetromino(tetromino, tetrominoX, tetrominoY);
        tetrominoX = 6;
        tetrominoY = 0;
        tetromino = tetrominos[GetRandomValue(0,6)];
        if (!TetrominoFits(tetromino, tetrominoX, tetrominoY)) {
          // TODO: proper loss screen
          goto EndApplication;
        }
      }
      // Check line clears
      bool markedLines[height];
      for (int j = 0; j < height-1; j++) {
        bool lineFilled = true;
        for (int i = 1; i < width-1; i++) {
          lineFilled = lineFilled && (board[i][j] != 0);
        }
        markedLines[j] = lineFilled;
        if (lineFilled)
          std::cout << "you filled a line!" << "\n";
      }
      GameTick = false;
    }

    // Drawing
    BeginDrawing();
      ClearBackground(Color{31,31,31,255});

      // Draw board
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          DrawRectangle(x*renderScale,y*renderScale,renderScale,renderScale,colors[board[x][y]]);
        }
      }

      DrawTetromino(tetromino, tetrominoX, tetrominoY);

    EndDrawing();
  }
  EndApplication:
  CloseWindow();
}
