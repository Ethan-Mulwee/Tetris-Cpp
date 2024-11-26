#ifndef TETRIS_APP
#define TETRIS_APP

#include "game.hpp"

class App {
  public:
    App(int windowWidth, int windowHeight);
  private:
    TetrisGame game;
};

#endif