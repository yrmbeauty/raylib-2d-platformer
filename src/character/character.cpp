#include "character.h"

#include <raylib.h>

#include "../../libs/physac.h"

#define VELOCITY 0.3f

Character::Character() {
  currentFrame = 0;
  framesCounter = 0;
  framesSpeed = 8;
  direction = 1;

  Init();
}

void Character::Init() {
  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();

  LoadTextures();

  frameRec = {0.0f, 0.0f, 0, 0};
  body = CreatePhysicsBodyRectangle((Vector2){(float) screenWidth / 2, (float) screenHeight / 2}, 26, 44, 1);
  body->freezeOrient = true;
  // body->enabled = false;
}

void Character::Update() {
  Controls();
  AnimationUpdate();
}

void Character::Draw() {
  AnimationDraw();

  DrawText(TextFormat("body->isGrounded: %i", body->isGrounded), 400, 200, 10, DARKGRAY);
  DrawText(TextFormat("body->velocity.y: %i", body->velocity.y), 400, 220, 10, DARKGRAY);
  DrawText(TextFormat("body->velocity.x: %i", body->velocity.x), 400, 240, 10, DARKGRAY);
}

void Character::LoadTextures() {
  Texture2D idle = LoadTexture("../src/resources/character/Idle.png");
  Texture2D run = LoadTexture("../src/resources/character/Run.png");
  Texture2D jump = LoadTexture("../src/resources/character/Jump.png");

  characterTextures = {idle, run, jump};
}

void Character::Controls() {
  if (IsKeyDown(KEY_RIGHT)) {
    body->velocity.x = VELOCITY;
    direction = 1;
  } else if (IsKeyDown(KEY_LEFT)) {
    body->velocity.x = -VELOCITY;
    direction = -1;
  } else if (body->isGrounded) {
    body->velocity.x *= 0.5;
  }


  if (IsKeyDown(KEY_UP) && body->isGrounded) {
    body->velocity.y = -VELOCITY * 4;
  }
}

void Character::AnimationUpdate() {
  auto [idle, run, jump] = characterTextures;

  if (!body->isGrounded) {
    currentTexture = jump;
    frameRec.width = direction * (float) jump.width / 3;
    frameRec.height = (float) jump.height;

    if (body->velocity.y < 0) {
      frameRec.x = (float) jump.width;
    } else if (body->velocity.y < 0.5) {
      frameRec.x = (float) jump.width / 3;
    } else {
      frameRec.x = 2 * (float) jump.width / 3;
    }
  }

  if (body->isGrounded) {
    currentTexture = idle;
    frameRec.width = direction * (float) idle.width / 10;
    frameRec.height = (float) idle.height;
    IdleAnimation();
  }
}

void Character::AnimationDraw() {
  Rectangle dest = {body->position.x - 32, body->position.y - 32, 64, 64};
  Vector2 origin = {0, 0};
  float rotation = 0;
  DrawTexturePro(currentTexture, frameRec, dest, origin, rotation, WHITE);
}

void Character::IdleAnimation() {
  framesCounter++;

  if (framesCounter >= (60 / framesSpeed)) {
    framesCounter = 0;
    currentFrame++;

    if (currentFrame > 9) currentFrame = 0;

    frameRec.x = (float) currentFrame * (float) characterTextures.idle.width / 10;
  }
}