#include "character.hpp"

#include <raylib.h>

#include <constants.hpp>

#define VELOCITY 0.3f

Character::Character() {
  currentFrame = 0;
  framesCounter = 0;
  framesSpeed = 8;
  direction = 1;

  Init();
}

void Character::Init() {
  // int screenWidth = GetScreenWidth();
  // int screenHeight = GetScreenHeight();

  LoadTextures();
}

void Character::Update() {
  Controls();
  AnimationUpdate();
}

void Character::Draw() {
  AnimationDraw();
}

void Character::LoadTextures() {
  Texture2D idle = LoadTexture(Constants::GetAssetPath("character/Idle.png").c_str());
  Texture2D run = LoadTexture(Constants::GetAssetPath("character/Run.png").c_str());
  Texture2D jump = LoadTexture(Constants::GetAssetPath("character/Jump.png").c_str());

  characterTextures = {idle, run, jump};
}

void Character::Controls() {
  // if (IsKeyDown(KEY_RIGHT)) {
  //   body->velocity.x = VELOCITY;
  //   direction = 1;
  // } else if (IsKeyDown(KEY_LEFT)) {
  //   body->velocity.x = -VELOCITY;
  //   direction = -1;
  // } else if (body->isGrounded) {
  //   body->velocity.x *= 0.5;
  // }

  // if (IsKeyDown(KEY_UP) && body->isGrounded) {
  //   body->velocity.y = -VELOCITY * 4;
  // }
}

void Character::AnimationUpdate() {
  auto [idle, run, jump] = characterTextures;

  // if (!body->isGrounded) {
  //   currentTexture = jump;
  //   frameRec.width = direction * (float)jump.width / 3;
  //   frameRec.height = (float)jump.height;

  //   if (body->velocity.y < 0) {
  //     frameRec.x = (float)jump.width;
  //   } else if (body->velocity.y < 0.5) {
  //     frameRec.x = (float)jump.width / 3;
  //   } else {
  //     frameRec.x = 2 * (float)jump.width / 3;
  //   }
  // }

  // if (body->isGrounded) {
  currentTexture = idle;
  frameRec.width = direction * (float)idle.width / 10;
  frameRec.height = (float)idle.height;
  IdleAnimation();
  // }
}

void Character::AnimationDraw() {
  Rectangle dest = {400 - 32, 200 - 32, 64, 64};
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

    frameRec.x = (float)currentFrame * (float)characterTextures.idle.width / 10;
  }
}