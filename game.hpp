#ifndef TETRIS_GAME
#define TETRIS_GAME

// STL
#include <iostream>
#include <chrono>
#include <algorithm>

#include <raylib.h>

#include "tetrominos.hpp"

class TetrisGame {
  public:
  // Tetris Game constructor, intializes the board to be blank
  TetrisGame();

  // Gets tetromino from queue
  Tetromino GetTetromino(int selection);

  // Move the active tetromino
  void Move(int x, int y);

  // Rotate the active tetromino
  void Rotate(int r);

  // Place the active tetromino
  void Place();

  // Do game loop
  void Update();

  // Do tetris logic
  void Tick();

  // Draw
  void Draw();

  private:
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

  void DrawTetromino(Tetromino tetromino, int x, int y) {
    for (int j = 0; j < 4; j++) {
      for (int i = 0; i < 4; i++) {
        DrawRectangle((i+x+boardOffsetX)*renderScale,(j+y+boardOffsetY)*renderScale,renderScale,renderScale,colors[tetromino.shape[i][j]]);
        DrawRectangle((i+x+boardOffsetX)*renderScale+2,(j+y+boardOffsetY)*renderScale+2,renderScale-4,renderScale-4,ColorBrightness(colors[tetromino.shape[i][j]],-0.1f));
      }
    }
  }

  void DrawPreview(Tetromino tetromino, int x, int y) {
    while(TetrominoFits(tetromino, x, y+1)) {
      y++;
    }
    for (int j = 0; j < 4; j++) {
      for (int i = 0; i < 4; i++) {
        Color color = colors[tetromino.shape[i][j]];
        color.a = 20;
        if (tetromino.shape[i][j] != 0)
          DrawRectangle((i+x+boardOffsetX)*renderScale,(j+y+boardOffsetY)*renderScale,renderScale,renderScale,color);
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

  // Add tetromino to board char array
  void AddTetromino(Tetromino tetromino, int x, int y) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (tetromino.shape[i][j] != 0) 
          board[i+x][j+y] = tetromino.shape[i][j];
      }
    }
  }

  // void PlaceTetromino() {
  //   AddTetromino(tetromino, tetrominoX, tetrominoY);
  //   tetrominoX = 4;
  //   tetrominoY = 0;
  //   tetromino = nextTetromino;
  //   nextTetromino = tetrominos[GetRandomValue(0,6)];
  //   swapped = false;
  // }

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

  // UI drawing functions
  void DrawTetrominoUI(Tetromino tetromino, int x, int y, float scale, const char* str) {
    // TODO: Refractor the draw tetromino function so you can use it here and avoid duplication
    DrawRectangle(x-5,y-5,4*scale+10,4*scale+10+20,Color{20,20,20,255});
    for (int j = 0; j < 4; j++) {
      for (int i = 0; i < 4; i++) {
        DrawRectangle((i)*scale+x,(j)*scale+y+20,scale,scale,colors[tetromino.shape[i][j]]);
        DrawRectangle((i)*scale+2+x,(j)*scale+2+y+20,scale-4,scale-4,ColorBrightness(colors[tetromino.shape[i][j]],-0.1f));
      }
    }
    DrawRectangleLines(x-5,y-5,4*scale+10,4*scale+10+20,WHITE);
    int leftX = x;
    int TopY = y;
    int RightX = x+4*scale;
    int BottomY = y+4*scale;

    DrawText(str, x, y, 20, WHITE);
  }

  public:
  const Color colors[10] = {Color{0,0,0,0}, LIGHTGRAY, YELLOW, BLUE, RED, GREEN, ORANGE, PINK, PURPLE};
  const static int width = 12;
  const static int height = 21;
  const int boardOffsetX = 0;
  const int boardOffsetY = 1;
  const int renderScale = 25;

  int score = 0;

  char board[width][height];
  int tetrominoX = 4;
  int tetrominoY = 0;

  // game state
  bool stored = false;
  bool swapped = false;
  bool suspended = false;

  int tetrominoQueue[7] = {0,1,2,3,4,5,6};
  int tetrominoSelection = 0;

  private:
  Tetromino currentTetromino = tetrominos[GetRandomValue(0,6)];
  Tetromino storedTetromino = Tetromino{
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0
  };

  // Timing
  std::chrono::steady_clock clock;
  std::chrono::steady_clock::time_point lastTickTime = clock.now();
  std::chrono::duration<double> deltaTickTime;
  std::chrono::duration<double> logicTickTimer;
  bool logicTick;
};

#endif 