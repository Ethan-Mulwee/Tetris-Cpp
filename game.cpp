#include "game.hpp"

void TetrisGame::Tick() {

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

  DrawTetromino(tetrominos[0] /* placeholder code */, tetrominoX, tetrominoY);
  DrawPreview(tetrominos[0] /* placeholder code */, tetrominoX, tetrominoY);

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
}
