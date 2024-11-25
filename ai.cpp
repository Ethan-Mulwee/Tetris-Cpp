#include "ai.hpp"
#include <iostream>

void TetrisAI::Update() {
  auto currentUpdateTime = clock.now();
  deltaTime = currentUpdateTime - lastUpdateTime;
  lastUpdateTime = currentUpdateTime;
  logicTimer += deltaTime;
  if (logicTimer.count() > 0.5f) {
      switch(GetRandomValue(0,1)) {
        case 0: 
          game->Tick(); 
          std::cout << TetrominoMatches(game->activeTetromino, game->activeX, game->activeY) << "\n";
          break;
        case 1: 
          game->Move(1,0);
          std::cout << TetrominoMatches(game->activeTetromino, game->activeX, game->activeY) << "\n";
          break;
        case 2: 
          game->Move(-1,0); break;
        case 3: 
          game->Move(1,0); break;
        case 4: 
          game->Move(-1,0); break;      
        case 5: 
          game->Rotate(1); break;
        case 6:
          game->Place(); break;
      }
    logicTimer = std::chrono::duration<double>();
  }
}

bool TetrisAI::TetrominoMatches(Tetromino tetromino, int x, int y) {
  while (game->TetrominoFits(tetromino, x, y+1)) {
    y++;
  }
  bool result = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (j < 3) {
        if (tetromino.shape[i][j] != 0 && tetromino.shape[i][j+1] == 0) {
          result = result && (game->board[i+x][j+y+1] != 0);
        }
      }
      else if (tetromino.shape[i][j] != 0) {
        result = result && (game->board[i+x][j+y+1] != 0);
      }
    }
  }
  return result;
}
