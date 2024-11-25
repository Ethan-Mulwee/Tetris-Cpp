#include "ai.hpp"

void TetrisAI::Update() {
  if (GetRandomValue(0,1)) {
    game->Place();
  }
  else {
    game->Move(1,0);
  }
}
