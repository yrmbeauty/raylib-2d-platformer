#include <raylib.h>

// #include "character/character.cpp"
// #include "character/character.h"

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "2D Platformer");

  SetTargetFPS(60);

  // Character character = Character();

  while (!WindowShouldClose()) {
    // character.Update();

    BeginDrawing();
    ClearBackground(WHITE);

    // character.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}