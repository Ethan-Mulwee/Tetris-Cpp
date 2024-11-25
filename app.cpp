#include <raylib.h>

#include "app.hpp"

App::App(int windowWidth, int windowHeight) {
  InitWindow(windowWidth, windowHeight, "Tetris");

  while (!WindowShouldClose()) {

    if (IsKeyPressed(KEY_RIGHT)) {
      game.Move(1,0);
    }
    if (IsKeyPressed(KEY_LEFT)) {
      game.Move(-1,0);
    }
    if (IsKeyPressed(KEY_UP)) {
      game.Rotate(1);
    }
    if (IsKeyPressed(KEY_DOWN)) {
      game.Tick();
    }

    game.Update();

    // Drawing
    BeginDrawing();
      game.Draw();
    EndDrawing();
  }
}

// // STL
// #include <iostream>
// #include <chrono>
// #include <string>
// #include <algorithm>

// #include <raylib.h>

// #include "app.hpp"
// #include "tetrominos.hpp"

// // Global vars
// const Color colors[10] = {Color{0,0,0,0}, LIGHTGRAY, YELLOW, BLUE, RED, GREEN, ORANGE, PINK, PURPLE};
// const int width = 12;
// const int height = 21;
// const int boardOffsetX = 0;
// const int boardOffsetY = 1;
// const int renderScale = 25;

// char board[width][height];
// int tetrominoX = 4;
// int tetrominoY = 0;

// // tetromino storage
// bool stored = false;
// bool swapped = false;

// int tetrominoPool[7] = {0,1,2,3,4,5,6};
// int tetrominoSelection = 0;

// // Misc functions

// void ShuffleArray(int* array, int size) {
//   for (int i = 0; i < size; i++) {
//     int r = GetRandomValue(0,size);
//     int temp = array[i];
//     array[i] = array[r];
//     array[r] = temp;
//   }
// }

// // Tetromino functions

// // Returns tetromino rotated
// Tetromino RotateTetromino(Tetromino tetromino, int times) {
//   Tetromino result;
//   for (int j = 0; j < 4; j++) {
//     for (int i = 0; i < 4; i++) {
//       // transposes for the moment
//       result.shape[i][j] = tetromino.shape[j][3-i];
//     }
//   }
//   return result;
// }

// // Check if tetromino its in board position
// bool TetrominoFits(Tetromino tetromino, int x, int y) {
//   bool result = true;
//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4; j++) {
//       result = result && !(tetromino.shape[i][j] != 0 && board[i+x][j+y] != 0);
//     }
//   }
//   return result;
// }

// void DrawTetromino(Tetromino tetromino, int x, int y) {
//   for (int j = 0; j < 4; j++) {
//     for (int i = 0; i < 4; i++) {
//       DrawRectangle((i+x+boardOffsetX)*renderScale,(j+y+boardOffsetY)*renderScale,renderScale,renderScale,colors[tetromino.shape[i][j]]);
//       DrawRectangle((i+x+boardOffsetX)*renderScale+2,(j+y+boardOffsetY)*renderScale+2,renderScale-4,renderScale-4,ColorBrightness(colors[tetromino.shape[i][j]],-0.1f));
//     }
//   }
// }

// void DrawPreview(Tetromino tetromino, int x, int y) {
//   while(TetrominoFits(tetromino, x, y+1)) {
//     y++;
//   }
//   for (int j = 0; j < 4; j++) {
//     for (int i = 0; i < 4; i++) {
//       Color color = colors[tetromino.shape[i][j]];
//       color.a = 20;
//       if (tetromino.shape[i][j] != 0)
//         DrawRectangle((i+x+boardOffsetX)*renderScale,(j+y+boardOffsetY)*renderScale,renderScale,renderScale,color);
//     }
//   }
// }

// void PrintTetromino(Tetromino tetromino) {
//   for (int j = 0; j < 4; j++) {
//     for (int i = 0; i < 4; i++) {
//       std::cout << (int)tetromino.shape[i][j];
//     }
//     std::cout << "\n";
//   }
// }

// Tetromino GetTetromino(int selection) {
//   return tetrominos[tetrominoPool[selection]];
// }


// // Add tetromino to board char array
// void AddTetromino(Tetromino tetromino, int x, int y) {
//   for (int i = 0; i < 4; i++) {
//     for (int j = 0; j < 4; j++) {
//       if (tetromino.shape[i][j] != 0) 
//         board[i+x][j+y] = tetromino.shape[i][j];
//     }
//   }
// }

// void PlaceTetromino(Tetromino &tetromino, Tetromino &nextTetromino, int x, int y) {
//   AddTetromino(tetromino, tetrominoX, tetrominoY);
//   tetrominoX = 4;
//   tetrominoY = 0;
//   tetromino = nextTetromino;
//   nextTetromino = tetrominos[GetRandomValue(0,6)];
//   swapped = false;
// }

// // Board functions
// bool CheckLine(int y) {
//   bool lineFilled = true;
//   for (int x = 1; x < width-1; x++) {
//     lineFilled = lineFilled && (board[x][y] != 0);
//   }
//   return lineFilled;
// }

// void ClearLine(int clearedY) {
//   for (int x = 1; x < width-1; x++) {
//     board[x][clearedY] = 0;
//     for (int y = clearedY-1; y >= 0; y--) {
//       board[x][y+1] = board[x][y];
//       board[x][y] = 0;
//     }
//   }
// }

// // UI drawing functions
// void DrawTetrominoUI(Tetromino tetromino, int x, int y, float scale, const char* str) {
//   // TODO: Refractor the draw tetromino function so you can use it here and avoid duplication
//   DrawRectangle(x-5,y-5,4*scale+10,4*scale+10+20,Color{20,20,20,255});
//   for (int j = 0; j < 4; j++) {
//     for (int i = 0; i < 4; i++) {
//       DrawRectangle((i)*scale+x,(j)*scale+y+20,scale,scale,colors[tetromino.shape[i][j]]);
//       DrawRectangle((i)*scale+2+x,(j)*scale+2+y+20,scale-4,scale-4,ColorBrightness(colors[tetromino.shape[i][j]],-0.1f));
//     }
//   }
//   DrawRectangleLines(x-5,y-5,4*scale+10,4*scale+10+20,WHITE);
//   int leftX = x;
//   int TopY = y;
//   int RightX = x+4*scale;
//   int BottomY = y+4*scale;

//   DrawText(str, x, y, 20, WHITE);
// }

// // TODO: sep game loop and app so you can restart the game without closing the app
// App::App(int windowWidth, int windowHeight) {
//   InitWindow(windowWidth,windowHeight, "Tetris");
//   InitAudioDevice();
//   SetTargetFPS(60);

//   Sound tetrisTheme = LoadSound("Tetris.mp3");

//   PlaySound(tetrisTheme);

//   ShuffleArray(tetrominoPool,7);
//   Tetromino tetromino = tetrominos[GetRandomValue(0,6)];
//   Tetromino nextTetromino = tetrominos[GetRandomValue(0,6)];
//   Tetromino storedTetromino = Tetromino{
//     0,0,0,0,
//     0,0,0,0,
//     0,0,0,0,
//     0,0,0,0
//   };

//   int score = 0;

//   // Timing
//   std::chrono::steady_clock clock;
//   auto lastFrameTime = clock.now();
//   std::chrono::duration<double> deltaTickTime;
//   std::chrono::duration<double> GameTimer;
//   bool GameTick;


  // // Inialized board state
  // for (int y = 0; y < height; y++) {
  //   for (int x = 0; x < width; x++) {
  //     if (y == height-1 || (x == 0 || x == width-1)) board[x][y] = 1;
  //     else board[x][y] = 0;
  //   }
  // }

//   // Game loop
//   while(!WindowShouldClose()) {
//     // TODO: cleanup timing code
//     // Timing 
//     auto currentFrameTime = clock.now();
//     deltaTickTime = currentFrameTime - lastFrameTime;
//     lastFrameTime = currentFrameTime;
//     GameTimer += deltaTickTime;
//     if (GameTimer.count() > 1) {
//       GameTick = true;
//       GameTimer = std::chrono::duration<double>();
//     }

//     // Input
//     if (IsKeyPressed(KEY_RIGHT))
//       if (TetrominoFits(tetromino, tetrominoX+1, tetrominoY))
//         tetrominoX += 1;
//     if (IsKeyPressedRepeat(KEY_RIGHT))
//       if (TetrominoFits(tetromino, tetrominoX+1, tetrominoY))
//         tetrominoX += 1;

//     if (IsKeyPressed(KEY_LEFT))
//       if (TetrominoFits(tetromino, tetrominoX-1, tetrominoY))
//         tetrominoX -= 1;
//     if (IsKeyPressedRepeat(KEY_LEFT))
//       if (TetrominoFits(tetromino, tetrominoX-1, tetrominoY))
//         tetrominoX -= 1;        

//     if (IsKeyPressed(KEY_DOWN))
//       if (TetrominoFits(tetromino, tetrominoX, tetrominoY+1)) {
//         GameTick = true;
//         GameTimer = std::chrono::duration<double>();
//       }
//     if (IsKeyPressedRepeat(KEY_DOWN))
//       if (TetrominoFits(tetromino, tetrominoX, tetrominoY+1)) {
//         GameTick = true;
//         GameTimer = std::chrono::duration<double>();
//       }
//     if (IsKeyPressed(KEY_UP)) {
//       Tetromino rotatedTetromino = RotateTetromino(tetromino, 1);
//       if (TetrominoFits(rotatedTetromino, tetrominoX, tetrominoY))
//         tetromino = rotatedTetromino;
//     }
//     if (IsKeyPressed(KEY_SPACE)) {
//       while(TetrominoFits(tetromino, tetrominoX, tetrominoY+1)) {
//         tetrominoY++;
//       }
//       GameTick = true;
//       GameTimer = std::chrono::duration<double>();
//     }
//     if (IsKeyPressed(KEY_S)) {
//       if (!stored) {
//         // TODO: standard swapping or adding 
//         storedTetromino = tetromino;
//         tetromino = nextTetromino;
//         nextTetromino = tetrominos[GetRandomValue(0,6)];
//         tetrominoX = 4;
//         tetrominoY = 0;
//         stored = true;
//         swapped = true;
//       }
//       else if (!swapped) {
//         Tetromino tempTetromino = tetromino;
//         tetromino = storedTetromino;
//         storedTetromino = tempTetromino;
//         tetrominoX = 4;
//         tetrominoY = 0;
//         swapped = true;
//       }
//     }

//     // Logic
//     if (GameTick) {
      // if(TetrominoFits(tetromino, tetrominoX, tetrominoY+1)) {
      //   tetrominoY += 1;
      // }
      // else {
      //   PlaceTetromino(tetromino, nextTetromino, tetrominoX, tetrominoY);
      //   if (!TetrominoFits(tetromino, tetrominoX, tetrominoY)) {
      //     // TODO: proper loss screen
      //     goto Loss;
      //   }
      // }
      // // Check line clears
      // bool markedLines[height-1] = {};
      // int ClearedLines = 0;
      // for (int j = 0; j < height-1; j++) {
      //   markedLines[j] = CheckLine(j);
      //   if (markedLines[j]) ClearedLines++;
      // }
      // // Add score
      // switch(ClearedLines) {
      //   case 0:
      //     break;
      //   case 1:
      //     score += 10;
      //     break;
      //   case 2:
      //     score += 20;
      //     break;
      //   case 3:
      //     score += 50;
      //     break;
      //   case 4:
      //     score += 100;
      //     break;
      // }

      // // Clear lines
      // for (int line = 0; line < height-1; line++) {
      //   if (markedLines[line]) {
      //     ClearLine(line);
      //   }
      // }
      // GameTick = false;
//     }

//     // Drawing
//     BeginDrawing();
      // ClearBackground(Color{31,31,31,255});

      // // Draw UI

      // int LeftX = (1+boardOffsetX)*renderScale;
      // int RightX = (width-1+boardOffsetX)*renderScale;
      // int BottomY = (height-1+boardOffsetY)*renderScale;
      // int TopY = (boardOffsetY)*renderScale;

      // // Draw Score
      // DrawRectangle(RightX+15, TopY, 300, 30, Color{20,20,20,255});
      // DrawLine(RightX+15, TopY, RightX+15+300, TopY, WHITE);
      // DrawLine(RightX+15, TopY+30, RightX+15+300, TopY+30, WHITE);
      // DrawLine(RightX+15, TopY, RightX+15, TopY+30, WHITE);
      // DrawLine(RightX+15+300, TopY, RightX+15+300, TopY+30, WHITE);

      // std::string scoreText = "SCORE: " + std::to_string(score);
      // DrawText(scoreText.c_str(), RightX+20, TopY, 30, WHITE);

      // // Draw Board shadow
      // DrawRectangle(LeftX+5, TopY+5, RightX - LeftX, BottomY - TopY, Color{20,20,20,100});

      // // Draw board background
      // DrawRectangle(LeftX, TopY, RightX - LeftX, BottomY - TopY, Color{20,20,20,255});
      
      // // Draw checker
      // for (int y = 0; y < height-1; y++) {
      //   for (int x = 1; x < width-1; x++) {
      //     if ((x+y)%2 == 1) {
      //       DrawRectangle((x+boardOffsetX)*renderScale,(y+boardOffsetY)*renderScale,renderScale,renderScale, Color{25,25,25,100});
      //     }
      //   }
      // }
      // DrawRectangleGradientV(LeftX, TopY, RightX - LeftX, BottomY - TopY, Color{255,255,255,0}, Color{10,10,10,50});

      // // Draw placed tetrominoes
      // for (int y = 0; y < height-1; y++) {
      //   for (int x = 1; x < width-1; x++) {
      //     DrawRectangle((x+boardOffsetX)*renderScale,(y+boardOffsetY)*renderScale,renderScale,renderScale,colors[board[x][y]]);
      //     DrawRectangle((x+boardOffsetX)*renderScale+2,(y+boardOffsetY)*renderScale+2,renderScale-4,renderScale-4,ColorBrightness(colors[board[x][y]],-0.1f));
      //   }
      // }

      // DrawTetromino(tetromino, tetrominoX, tetrominoY);
      // DrawPreview(tetromino, tetrominoX, tetrominoY);

      // // Draw board borders
      
      // // Right vertical
      // DrawLine(RightX, TopY, RightX, BottomY, WHITE);
      // // Left vertical
      // DrawLine(LeftX, TopY, LeftX, BottomY, WHITE);
      // // Bottom horizontal
      // DrawLine(LeftX, BottomY, RightX, BottomY, WHITE);
      // // Top horizontal
      // DrawLine(LeftX, TopY, RightX, TopY, WHITE);

      // DrawTetrominoUI(storedTetromino, RightX+20, TopY+40, 33, "STORED: ");
      // DrawTetrominoUI(nextTetromino, RightX+178, TopY+40, 33, "NEXT: ");

//     EndDrawing();
//   }
//   Loss:
//   while(!WindowShouldClose()) {
//     BeginDrawing();
//       DrawRectangle(0,0,windowWidth, windowHeight, Color{30,30,30,5});
//       DrawText("GAME OVER", 85,5, 20, WHITE);
//     EndDrawing();
//   }
//   CloseWindow();
// }
