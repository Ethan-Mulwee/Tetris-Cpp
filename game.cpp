#include "game.hpp"

#include <ctime>

TetrisGame::TetrisGame() {
  // TODO: cleanup intialization code
  SetRandomSeed(time(0));
  Shuffle(tetrominoQueue_F);
  Shuffle(tetrominoQueue_B);
  queueSelection = false;
  tetrominoSelection = 0;
  for (int i = 0; i < 7; i++) {
    std::cout << tetrominoQueue_F[i] << "\n";
  }
  activeTetromino = GetTetromino(tetrominoSelection);
  gameSpeed = 0.65f;
}

Tetromino TetrisGame::GetTetromino(int selection)
{
  if (!queueSelection) {
    if (selection > 6) {
      return tetrominos[tetrominoQueue_B[selection-7]];
    }
    return tetrominos[tetrominoQueue_F[selection]];
  }
  else {
    if (selection > 6) {
      return tetrominos[tetrominoQueue_F[selection-7]];
    }
    return tetrominos[tetrominoQueue_B[selection]];
  }
}

void TetrisGame::Move(int x, int y) {
  if (board.Fits(activeTetromino, activeX+x, activeY+y)) {
    activeX += x;
    activeY += y;
  }
}

void TetrisGame::Rotate(int r) {
  if (board.Fits(activeTetromino.Rotated(r), activeX, activeY))
    activeTetromino.Rotate(r);
}

void TetrisGame::Place() {
  while(board.Fits(activeTetromino, activeX, activeY+1)) {
    activeY++;
  }
  board.Add(activeTetromino, activeX, activeY);
  Check();
  Next();
  // gameSpeed -= 0.05f*gameSpeed;
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
  if (logicTimer.count() > gameSpeed) {
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

void TetrisGame::Draw(float renderScale, float renderX, float renderY) {
  ClearBackground(Color{31,31,31,255});

  // Draw UI

  int LeftX =  (1+boardOffsetX)*renderScale+renderX;
  int RightX = (board.width-1+boardOffsetX)*renderScale+renderX;
  int BottomY = (board.height-1+boardOffsetY)*renderScale+renderY;
  int TopY =    (boardOffsetY)*renderScale+renderY;

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
        DrawRectangle(
        (x+boardOffsetX)*renderScale+renderX,
        (y+boardOffsetY)*renderScale+renderY,
        renderScale,
        renderScale, 
        Color{25,25,25,100}
        );
      }
    }
  }
  DrawRectangleGradientV(LeftX, TopY, RightX - LeftX, BottomY - TopY, Color{255,255,255,0}, Color{10,10,10,50});

  // Draw placed tetrominoes
  for (int y = 0; y < height-1; y++) {
    for (int x = 1; x < width-1; x++) {
      DrawRectangle((x+boardOffsetX)*renderScale+renderX,(y+boardOffsetY)*renderScale+renderY,renderScale,renderScale,colors[board[x][y]]);
      DrawRectangle((x+boardOffsetX)*renderScale+renderX+2,(y+boardOffsetY)*renderScale+renderY+2,renderScale-4,renderScale-4,ColorBrightness(colors[board[x][y]],-0.1f));
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
  DrawTetrominoUI(GetTetromino(tetrominoSelection+1), RightX+178, TopY+40, 33, "NEXT: ");

  if (over) {
    DrawRectangle(0,0,600, 600, Color{30,30,30,5});
    DrawText("GAME OVER", 85,5, 20, WHITE);
  }
  // Debug code
  // std::string queueSelectionState = "queueSelection: " + std::to_string(queueSelection);
  // DrawText(queueSelectionState.c_str(), 400, 200, 20, WHITE);
  BoardEval();
}

void TetrisGame::BoardEval() {
  int holes = 0;
  int aggregateHeight = 0;
  float bump = 0;
  for (int x = 1; x < width-1; x++) {
    for (int y = 0; y < height-1; y++) {
      if (board[x][y] != 0 && board[x][y+1] == 0)
        holes++;
      if (board[x][y] != 0)
        aggregateHeight++;
    }
  }

  std::string holeStr = "holes: " + std::to_string(holes);
  DrawText(holeStr.c_str(), 300, 250, 20, WHITE);
  std::string heightStr = "height: " + std::to_string(aggregateHeight);
  DrawText(heightStr.c_str(), 420, 250, 20, WHITE);
}
