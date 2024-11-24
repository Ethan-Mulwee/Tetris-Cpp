// STL
#include <iostream>
#include <chrono>
#include <algorithm>

#include <raylib.h>

#include "tetrominos.hpp"

class TetrisGame {
  public:
  // Gets tetromino from queue
  Tetromino GetTetromino(int selection);

  // Move tetromino
  void MoveTetromino(int x, int y);

  // Do game loop
  void Tick();

  // Draw
  void Draw();
  
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