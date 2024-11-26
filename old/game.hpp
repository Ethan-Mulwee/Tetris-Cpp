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

  // Gets tetromino from queue
  Tetromino GetTetromino(int selection);

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

  // NOTE: temp
  void BoardEval();

  // TODO: should be private sort out AI functions for tetrominos in tetrminos hpp
  public:

  void DrawPreview(Tetromino tetromino, int x, int y);

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
  Color colors[10] = {Color{0,0,0,0}, LIGHTGRAY, YELLOW, BLUE, RED, GREEN, ORANGE, PINK, PURPLE};
  const int boardOffsetX = 0;
  const int boardOffsetY = 1;

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
  // TODO: should be private sort out tetromino functions for AI
  public:
  Tetromino activeTetromino;
  Tetromino storedTetromino = Tetromino{
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0
  };

  // Timing
  float gameSpeed;

  std::chrono::steady_clock clock;
  std::chrono::steady_clock::time_point lastUpdateTime = clock.now();
  std::chrono::duration<double> deltaTime;
  std::chrono::duration<double> logicTimer;
  std::chrono::duration<double> suspendTimer;
  bool logicTick;
};

#endif 