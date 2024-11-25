#include "game.hpp"

#include <ctime>

TetrisGame::TetrisGame() {
  SetRandomSeed(time(0));
  // Inialize board state
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (y == height-1 || (x == 0 || x == width-1)) board[x][y] = 1;
      else board[x][y] = 0;
    }
  }
  Shuffle(tetrominoQueue_F);
  Shuffle(tetrominoQueue_B);
  activeTetromino = tetrominos[tetrominoQueue_F[tetrominoSelection]];
}

Tetromino TetrisGame::GetTetromino(int selection)
{
  if (queueSelection) {
    if (selection > 6) {
      return tetrominos[tetrominoQueue_B[selection]];
    }
    return tetrominos[tetrominoQueue_F[selection]];
  }
  else {
    if (selection > 6) {
      return tetrominos[tetrominoQueue_F[selection]];
    }
    return tetrominos[tetrominoQueue_B[selection]];
  }
}

void TetrisGame::Move(int x, int y) {
  if (suspended) return;
  if (TetrominoFits(activeTetromino, activeX+x, activeY+y)) {
    activeX += x;
    activeY += y;
  }
}

void TetrisGame::Rotate(int r) {
  if (suspended) return;
  if (TetrominoFits(RotateTetromino(activeTetromino, r), activeX, activeY))
    activeTetromino = RotateTetromino(activeTetromino, r);
}

void TetrisGame::Place() {
  if (suspended) return;
  while(TetrominoFits(activeTetromino, activeX, activeY+1)) {
    activeY++;
  }
  AddTetromino(activeTetromino, activeX, activeY);
  Check();
  Next();
}

void TetrisGame::Next() {
  activeX = 4;
  activeY = 0;
  tetrominoSelection++;
  if (tetrominoSelection == 7) {
    tetrominoSelection = 0;
    Shuffle(tetrominoQueue_F);
  }
  activeTetromino = GetTetromino(tetrominoSelection);
  // Check for loss
  if (!TetrominoFits(activeTetromino, activeX, activeY)) {
    over = true;
  }
  // game state
  logicTimer = std::chrono::duration<double>();
  swapped = false;
}

void TetrisGame::Swap() {
  // if the player already swapped
  if (swapped) return;
  if (stored) {
    Tetromino temp = activeTetromino;
    activeTetromino = storedTetromino;
    storedTetromino = temp;
    activeX = 4;
    activeY = 0;
  }
  else {
    storedTetromino = activeTetromino;
    stored = true;
    Next();
  }
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
  if (logicTimer.count() > 1) {
    logicTimer = std::chrono::duration<double>();
    Tick();
  }
}

void TetrisGame::Tick() {
  if (suspended) return;
  if(TetrominoFits(activeTetromino, activeX, activeY+1)) {
    activeY += 1;
  }
  else {
    Place();
    if (!TetrominoFits(activeTetromino, activeX, activeY)) {
      // TODO: proper loss screen
      // goto Loss;
    }
  }
  Check();
}

void TetrisGame::Check() {
  // Check line clears
  bool markedLines[height-1] = {};
  int ClearedLines = 0;
  for (int j = 0; j < height-1; j++) {
    markedLines[j] = CheckLine(j);
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
  for (int line = 0; line < height-1; line++) {
    if (markedLines[line]) {
      ClearLine(line);
    }
  }
}

void TetrisGame::Draw() {
  ClearBackground(Color{31,31,31,255});

  // Draw UI

  int LeftX = (1+boardOffsetX)*renderScale;
  int RightX = (width-1+boardOffsetX)*renderScale;
  int BottomY = (height-1+boardOffsetY)*renderScale;
  int TopY = (boardOffsetY)*renderScale;

  // Draw Score
  DrawRectangle(RightX+15, TopY, 300, 30, Color{20,20,20,255});
  DrawLine(RightX+15, TopY, RightX+15+300, TopY, WHITE);
  DrawLine(RightX+15, TopY+30, RightX+15+300, TopY+30, WHITE);
  DrawLine(RightX+15, TopY, RightX+15, TopY+30, WHITE);
  DrawLine(RightX+15+300, TopY, RightX+15+300, TopY+30, WHITE);

  std::string scoreText = "SCORE: " + std::to_string(score);
  DrawText(scoreText.c_str(), RightX+20, TopY, 30, WHITE);

  // Draw Board shadow
  DrawRectangle(LeftX+5, TopY+5, RightX - LeftX, BottomY - TopY, Color{20,20,20,100});

  // Draw board background
  DrawRectangle(LeftX, TopY, RightX - LeftX, BottomY - TopY, Color{20,20,20,255});
  
  // Draw checker
  for (int y = 0; y < height-1; y++) {
    for (int x = 1; x < width-1; x++) {
      if ((x+y)%2 == 1) {
        DrawRectangle((x+boardOffsetX)*renderScale,(y+boardOffsetY)*renderScale,renderScale,renderScale, Color{25,25,25,100});
      }
    }
  }
  DrawRectangleGradientV(LeftX, TopY, RightX - LeftX, BottomY - TopY, Color{255,255,255,0}, Color{10,10,10,50});

  // Draw placed tetrominoes
  for (int y = 0; y < height-1; y++) {
    for (int x = 1; x < width-1; x++) {
      DrawRectangle((x+boardOffsetX)*renderScale,(y+boardOffsetY)*renderScale,renderScale,renderScale,colors[board[x][y]]);
      DrawRectangle((x+boardOffsetX)*renderScale+2,(y+boardOffsetY)*renderScale+2,renderScale-4,renderScale-4,ColorBrightness(colors[board[x][y]],-0.1f));
    }
  }

  DrawTetromino(activeTetromino /* placeholder code */, activeX, activeY);
  DrawPreview(activeTetromino /* placeholder code */, activeX, activeY);

  // Draw board borders
  
  // Right vertical
  DrawLine(RightX, TopY, RightX, BottomY, WHITE);
  // Left vertical
  DrawLine(LeftX, TopY, LeftX, BottomY, WHITE);
  // Bottom horizontal
  DrawLine(LeftX, BottomY, RightX, BottomY, WHITE);
  // Top horizontal
  DrawLine(LeftX, TopY, RightX, TopY, WHITE);

  DrawTetrominoUI(storedTetromino, RightX+20, TopY+40, 33, "STORED: ");
  //DrawTetrominoUI(nextTetromino, RightX+178, TopY+40, 33, "NEXT: ");

  if (over) {
    DrawRectangle(0,0,600, 600, Color{30,30,30,5});
    DrawText("GAME OVER", 85,5, 20, WHITE);
  }
}
