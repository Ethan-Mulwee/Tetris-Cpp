#include "ai.hpp"

void TetrisAI::Update() {
  auto currentUpdateTime = clock.now();
  deltaTime = currentUpdateTime - lastUpdateTime;
  lastUpdateTime = currentUpdateTime;
  logicTimer += deltaTime;
  if (logicTimer.count() > 0.5f) {
    if ((game->board[10][19]) == 0) {
      switch(GetRandomValue(0,6)) {
        case 0: 
          game->Tick(); break;
        case 1: 
          game->Move(1,0); break;
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
    }
    else {
      game->Place();
    }
    logicTimer = std::chrono::duration<double>();
  }
}
