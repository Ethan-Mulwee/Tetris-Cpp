#include <raylib.h>
#include <ctime>

#include "app.hpp"

App::App(int windowWidth, int windowHeight) {
  InitWindow(windowWidth, windowHeight, "Tetris");

  game.renderPosX = 0;
  game.renderPosY = 0;

  SetRandomSeed(time(0)+1);
  TetrisGame game2;
  game2.renderPosX = 600;

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

    if (IsKeyPressed(KEY_Z)) game.Swap();

    if (IsKeyPressed(KEY_P)) game.suspended = !game.suspended;

    // Game2 input
    if (IsKeyPressed(KEY_D)) game2.Move(1,0);
    if (IsKeyPressedRepeat(KEY_D)) game2.Move(1,0);

    if (IsKeyPressed(KEY_A)) game2.Move(-1,0);
    if (IsKeyPressedRepeat(KEY_A)) game2.Move(-1,0);

    if (IsKeyPressed(KEY_W)) game2.Rotate(1);
    if (IsKeyPressedRepeat(KEY_W)) game2.Rotate(1);

    if (IsKeyPressed(KEY_S)) game2.Tick();
    if (IsKeyPressedRepeat(KEY_S)) game2.Tick();

    if (IsKeyPressed(KEY_E)) game2.Place();

    if (IsKeyPressed(KEY_Q)) game2.Swap();

    game.Update();
    game2.Update();

    // Drawing
    BeginDrawing();
      game.Draw();
      game2.Draw();
    EndDrawing();
  }
}
