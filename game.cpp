#include "game.hpp"

void TetrisGame::Move(int x, int y) {
  if (board.Fits(activeTetromino, activeX+x,activeY+y)) {
    activeX+x;
    activeY+y;
  }
}

void TetrisGame::Rotate(int r) {
  if (board.Fits(activeTetromino.Rotated(r), activeX, activeY)) {
    activeTetromino.Rotate(r);
  }
}

void TetrisGame::Place() {
  while(board.Fits(activeTetromino, activeX, activeY+1))
    activeY++;
  board.Add(activeTetromino, activeX, activeY);
  Check();
  Next();
}

void TetrisGame::Next() {
  activeX = 4;
  activeY = 0;
  tetrominoSelection++;
  if (tetrominoSelection == 7) {
    tetrominoSelection = 0;
    queueSelection = !queueSelection;
    if (queueSelection)
      Shuffle(tetrominoQueue_F);
    else
      Shuffle(tetrominoQueue_B);
  }
  activeTetromino = GetTetromino(tetrominoSelection);
  // Check for loss
  if (!board.Fits(activeTetromino, activeX, activeY)) {
    over = true;
  }
  // game state
  logicTimer = std::chrono::duration<double>();
  swapped = false;
}

void TetrisGame::Shuffle(int* array) {
  for (int i = 0; i < 7; i++) {
    int r = GetRandomValue(0,6);
    int temp = array[i];
    array[i] = array[r];
    array[r] = temp;
  }
}

void TetrisGame::Update() {
  auto currentUpdateTime = clock.now();
  deltaTime = currentUpdateTime - lastUpdateTime;
  lastUpdateTime = currentUpdateTime;
  logicTimer += deltaTime;
  if (logicTimer.count() > gameRate) {
    logicTimer = std::chrono::duration<double>();
    Tick();
  }
  if (suspended) {
    suspendTimer += deltaTime;
    if (suspendTimer.count() > 1.0f) {
      suspendTimer = std::chrono::duration<double>();
      suspended = false;
    }
  }
}

void TetrisGame::Tick() {
  if (suspended) return;
  if(board.Fits(activeTetromino, activeX, activeY+1)) {
    activeY += 1;
  }
  else {
    Place();
    if (!board.Fits(activeTetromino, activeX, activeY)) {
      // TODO: proper loss screen
      // goto Loss;
    }
  }
  Check();
}

void TetrisGame::Check() {
  // Check line clears
  bool markedLines[board.height-1] = {};
  int ClearedLines = 0;
  for (int j = 0; j < board.height-1; j++) {
    markedLines[j] = board.CheckLine(j);
    if (markedLines[j]) ClearedLines++;
  }
  // Add score
  switch(ClearedLines) {
    case 0:
      break;
    case 1:
      score += 10;
      break;
    case 2:
      score += 20;
      break;
    case 3:
      score += 50;
      break;
    case 4:
      score += 100;
      break;
  }

  // Clear lines
  for (int line = 0; line < board.height-1; line++) {
    if (markedLines[line]) {
      board.ClearLine(line);
    }
  }
}