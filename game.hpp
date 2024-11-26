#ifndef TETRIS_GAME
#define TETRIS_GAME

// STL
#include <iostream>
#include <chrono>
#include <algorithm>

#include <raylib.h>

#include "tetromino.hpp"
#include "board.hpp"

class TetrisGame {
  public:
  // Tetris Game constructor, intializes values
  TetrisGame();

  // Move the active tetromino
  void Move(int x, int y);

  // Rotate the active tetromino
  void Rotate(int r);

  // Place the active tetromino
  void Place();

  // Go to the next tetromino in queue
  void Next();

  // Swaps the stored tetromino and active
  void Swap();

  // Shuffles tetromino queue
  void Shuffle(int* array);

  // Do game loop
  void Update();

  // Do tetris logic
  void Tick();

  // Handle line clears
  void Check();

  // Draw game
  void Draw(float renderScale, float renderX, float renderY);

  private:

  void DrawPreview(Tetromino tetromino, int x, int y);

  void DrawTetromino(Tetromino tetromino, int x, int y);

  void DrawTetrominoUI(Tetromino tetromino, int x, int y, float scale, const char* str);

  // Gets tetromino from queue
  Tetromino GetTetromino(int selection);

  private:
  Color colors[10] = {Color{0,0,0,0}, LIGHTGRAY, YELLOW, BLUE, RED, GREEN, ORANGE, PINK, PURPLE};

  int score = 0;

  Board board;
  int activeX = 4;
  int activeY = 0;

  // game state
  bool stored = false;
  bool swapped = false;
  bool suspended = false;
  bool over = false;

  int tetrominoQueue_F[7] = {0,1,2,3,4,5,6};
  int tetrominoQueue_B[7] = {0,1,2,3,4,5,6};
  int tetrominoSelection = 0;
  bool queueSelection;

  Tetromino activeTetromino;
  Tetromino storedTetromino = Tetromino{
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0
  };

  // Timing
  float gameRate;

  std::chrono::steady_clock clock;
  std::chrono::steady_clock::time_point lastUpdateTime = clock.now();
  std::chrono::duration<double> deltaTime;
  std::chrono::duration<double> logicTimer;
  std::chrono::duration<double> suspendTimer;
  bool logicTick;
};

#endif 