#include <raylib.h>

#include "character/character.cpp"
#include "character/character.h"

#define PHYSAC_IMPLEMENTATION
#include "../libs/physac.h"

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "MyGame");

  InitPhysics();
  SetPhysicsGravity(0, 4);
  SetTargetFPS(60);

  PhysicsBody floor = CreatePhysicsBodyRectangle((Vector2){(float) screenWidth / 2, screenHeight - 20}, screenWidth, 10, 1);
  PhysicsBody platformLeft = CreatePhysicsBodyRectangle((Vector2){screenWidth * 0.25f, screenHeight * 0.7f}, screenWidth * 0.25f, 10, 1);
  PhysicsBody platformRight = CreatePhysicsBodyRectangle((Vector2){screenWidth * 0.75f, screenHeight * 0.8f}, screenWidth * 0.25f, 10, 1);
  PhysicsBody wallLeft = CreatePhysicsBodyRectangle((Vector2){0, (float) screenHeight / 2}, 1, screenHeight, 1);
  PhysicsBody wallRight = CreatePhysicsBodyRectangle((Vector2){screenWidth, (float) screenHeight / 2}, 1, screenHeight, 1);

  floor->enabled = false;
  platformLeft->enabled = false;
  platformRight->enabled = false;
  wallLeft->enabled = false;
  wallRight->enabled = false;

  Character character = Character();

  while (!WindowShouldClose()) {
    character.Update();

    BeginDrawing();
    ClearBackground(WHITE);

    character.Draw();

    int bodiesCount = GetPhysicsBodiesCount();
    for (int i = 0; i < bodiesCount - 1; i++) {
      PhysicsBody body = GetPhysicsBody(i);

      int vertexCount = GetPhysicsShapeVerticesCount(i);
      for (int j = 0; j < vertexCount; j++) {
        Vector2 vertexA = GetPhysicsShapeVertex(body, j);

        int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);
        Vector2 vertexB = GetPhysicsShapeVertex(body, jj);

        DrawLineV(vertexA, vertexB, GREEN);
      }
    }

    EndDrawing();
  }

  ClosePhysics();
  CloseWindow();
  return 0;
}