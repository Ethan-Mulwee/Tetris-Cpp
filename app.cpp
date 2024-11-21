// STL
#include <iostream>
#include <chrono>
#include <string>

#include <raylib.h>

#include "app.hpp"
#include "tetrominos.hpp"

// Global vars
const Color colors[10] = {Color{0,0,0,0}, LIGHTGRAY, YELLOW, BLUE, RED, GREEN, ORANGE, PINK, PURPLE};
const int width = 12;
const int height = 21;
char board[width][height];
const int boardOffsetX = 0;
const int boardOffsetY = 1;
const int renderScale = 25;


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
      DrawRectangle((i+x+boardOffsetX)*renderScale,(j+y+boardOffsetY)*renderScale,renderScale,renderScale,colors[tetromino.shape[i][j]]);
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

// Board functions
bool CheckLine(int y) {
  bool lineFilled = true;
  for (int x = 1; x < width-1; x++) {
    lineFilled = lineFilled && (board[x][y] != 0);
  }
  return lineFilled;
}

void ClearLine(int clearedY) {
  for (int x = 1; x < width-1; x++) {
    board[x][clearedY] = 0;
    for (int y = clearedY-1; y >= 0; y--) {
      board[x][y+1] = board[x][y];
      board[x][y] = 0;
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

  int score;

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
      bool markedLines[height-1] = {};
      for (int j = 0; j < height-1; j++) {
        markedLines[j] = CheckLine(j);
      }
      for (int line = 0; line < height-1; line++) {
        if (markedLines[line]) {
          ClearLine(line);
        }
      }
      GameTick = false;
    }

    // Drawing
    BeginDrawing();
      ClearBackground(Color{31,31,31,255});

      // Draw UI

      int LeftX = (1+boardOffsetX)*renderScale;
      int RightX = (width-1+boardOffsetX)*renderScale;
      int BottomY = (height-1+boardOffsetY)*renderScale;
      int TopY = (boardOffsetY)*renderScale;


      DrawText("score: ", RightX+20, TopY, 50, WHITE);

      // Draw board background
      DrawRectangle(LeftX, TopY, RightX - LeftX, BottomY - TopY, Color{20,20,20,255});

      // Draw placed tetrominoes
      for (int y = 0; y < height-1; y++) {
        for (int x = 1; x < width-1; x++) {
          DrawRectangle((x+boardOffsetX)*renderScale,(y+boardOffsetY)*renderScale,renderScale,renderScale,colors[board[x][y]]);
        }
      }
      // Draw board borders
      
      // Right vertical
      DrawLine(RightX, TopY, RightX, BottomY, WHITE);
      // Left vertical
      DrawLine(LeftX, TopY, LeftX, BottomY, WHITE);
      // Bottom horizontal
      DrawLine(LeftX, BottomY, RightX, BottomY, WHITE);
      // Top horizontal
      DrawLine(LeftX, TopY, RightX, TopY, WHITE);

      DrawTetromino(tetromino, tetrominoX, tetrominoY);

    EndDrawing();
  }
  EndApplication:
  CloseWindow();
}
