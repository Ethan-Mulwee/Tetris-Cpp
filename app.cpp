#include <raylib.h>

#include "app.hpp"
#include "ai.hpp"
#include "board.hpp"

App::App(int windowWidth, int windowHeight) {
  InitWindow(windowWidth, windowHeight, "Tetris");

  // TetrisAI ai;
  // ai.game = &game;

  Board board;
  Color colors[10] = {Color{0,0,0,0}, LIGHTGRAY, YELLOW, BLUE, RED, GREEN, ORANGE, PINK, PURPLE};

  while (!WindowShouldClose()) {
    // Game input
    if (IsKeyPressed(KEY_RIGHT)) game.Move(1,0);
    if (IsKeyPressedRepeat(KEY_RIGHT)) game.Move(1,0);

    if (IsKeyPressed(KEY_LEFT)) game.Move(-1,0);
    if (IsKeyPressedRepeat(KEY_LEFT)) game.Move(-1,0);

    if (IsKeyPressed(KEY_UP)) game.Rotate(1);
    if (IsKeyPressedRepeat(KEY_UP)) game.Rotate(1);

    if (IsKeyPressed(KEY_DOWN)) game.Tick();
    if (IsKeyPressedRepeat(KEY_DOWN)) game.Tick();

    if (IsKeyPressed(KEY_SPACE)) game.Place();

    if (IsKeyPressed(KEY_S)) game.Swap();

    // ai.Update();
    game.Update();

    // Drawing
    BeginDrawing();
      game.Draw(25,0,0);
    EndDrawing();
  }
}
