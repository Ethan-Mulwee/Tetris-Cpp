#ifndef TETRIS_AI
#define TETRIS_AI

#include "game.hpp"

#include <chrono>

class TetrisAI {
  public:
    void Update();
    TetrisGame* game;
  private:
    std::chrono::steady_clock clock;
    std::chrono::steady_clock::time_point lastUpdateTime = clock.now();
    std::chrono::duration<double> deltaTime;
    std::chrono::duration<double> logicTimer;
  public:

  private:
    // Returns true if tetromino will make a perfect match when placed
    bool TetrominoMatches(Tetromino tetromino, int x, int y);
};

#endif