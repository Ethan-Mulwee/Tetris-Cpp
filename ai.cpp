#include "ai.hpp"

void TetrisAI::Update() {
  auto currentUpdateTime = clock.now();
  deltaTime = currentUpdateTime - lastUpdateTime;
  lastUpdateTime = currentUpdateTime;
  logicTimer += deltaTime;
  if (logicTimer.count() > 0.5f) {
    switch(GetRandomValue(0,3)) {
      case 0: 
        game->Tick(); break;
      case 1: 
        game->Move(1,0); break;
      case 2: 
        game->Move(-1,0); break;
      case 3: 
        game->Rotate(1); break;
    }
    logicTimer = std::chrono::duration<double>();
  }
}
