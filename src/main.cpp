#include <raylib.h>

#include "character/character.hpp"

void DrawBodyes(b2World *world);

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  b2Vec2 gravity(0.0f, 60.0f);
  b2World world(gravity);

  const float groundX = screenWidth / 2;
  const float groundY = screenHeight / 2 + 40.0f;
  const float groundWidth = screenWidth / 10;
  const float groundHeight = 1.0f;

  b2BodyDef groundDef;
  groundDef.position.Set(groundX, groundY);
  b2Body *groundBody = world.CreateBody(&groundDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(groundWidth, groundHeight);
  groundBody->CreateFixture(&groundBox, 0.0f);

  b2BodyDef platformDef;
  platformDef.position.Set(groundX - 50, groundY - 10);
  b2Body *platform = world.CreateBody(&platformDef);
  b2PolygonShape platformBox;
  platformBox.SetAsBox(groundWidth / 4, groundHeight);
  platform->CreateFixture(&platformBox, 0.0f);

  b2BodyDef platform2Def;
  platform2Def.position.Set(groundX + 30, groundY - 12);
  b2Body *platform2 = world.CreateBody(&platform2Def);
  b2PolygonShape platform2Box;
  platform2Box.SetAsBox(groundWidth / 4, groundHeight);
  platform2->CreateFixture(&platform2Box, 0.0f);

  InitWindow(screenWidth, screenHeight, "2D Platformer");
  SetTargetFPS(60);

  Character character = Character(&world);

  float timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 6;
  int32 positionIterations = 2;

  Camera2D camera;
  camera.target = character.getPosition();
  camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 4.0f * 3};
  camera.rotation = 0.0f;
  camera.zoom = 8.0f;

  while (!WindowShouldClose()) {
    world.Step(timeStep, velocityIterations, positionIterations);
    character.Update();
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 4.0f * 3};
    camera.target = character.getPosition();

    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode2D(camera);

    character.Draw();
    DrawBodyes(&world);

    EndMode2D();

    Vector2 velocity = character.getVelocity();
    DrawText(TextFormat("velocityX: %i", velocity.x), 10, 10, 10, BLACK);
    DrawText(TextFormat("velocityY: %i", velocity.y), 10, 20, 10, BLACK);

    Vector2 positioin = character.getPosition();
    DrawText(TextFormat("positioinX: %i", positioin.x), 10, 30, 10, BLACK);
    DrawText(TextFormat("positioinY: %i", positioin.y), 10, 40, 10, BLACK);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

void DrawBodyes(b2World *world) {
  auto currentBody = world->GetBodyList();
  while (currentBody != nullptr) {
    auto pos = currentBody->GetPosition();
    // DrawCircle(pos.x, pos.y, 2, PURPLE);

    auto fixture = currentBody->GetFixtureList();
    while (fixture != nullptr) {
      auto shape = fixture->GetShape();

      auto polygonShape = (b2PolygonShape *)shape;
      int vertexCount = 4;
      for (int j = 0; j < vertexCount; j++) {
        b2Vec2 vertexA = polygonShape->m_vertices[j];

        int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);
        b2Vec2 vertexB = polygonShape->m_vertices[jj];

        DrawLineV({(pos.x + vertexA.x), (pos.y + vertexA.y)},
                  {(pos.x + vertexB.x), (pos.y + vertexB.y)}, GREEN);
      }

      fixture = fixture->GetNext();
    }

    currentBody = currentBody->GetNext();
  }
}