#include <raylib.h>

#include "app.hpp"
#include "ai.hpp"
#include "board.hpp"

App::App(int windowWidth, int windowHeight) {
  InitWindow(windowWidth, windowHeight, "Tetris");

  game.gameSpeed = 100;

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

    if (IsKeyPressed(KEY_P)) game.suspended = !game.suspended;

    // ai.Update();
    game.Update();

    // Drawing
    BeginDrawing();
      game.Draw(22,0,0);
      board.Draw(50,50, 25, colors);
    EndDrawing();
  }
}
