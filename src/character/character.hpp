#pragma once

#include <box2d/box2d.h>
#include <raylib.h>

struct CharacterTextures {
  Texture2D idle;
  Texture2D run;
  Texture2D jump;
};

class Character {
 private:
  b2Body *body{};
  b2World *world{};
  bool isGrounded;

  float bodyX;
  float bodyY;
  float bodyWidth;
  float bodyHeight;

  Rectangle frameRec{};
  CharacterTextures characterTextures{};
  Texture2D currentTexture{};
  int currentFrame;
  int framesCounter;
  int framesSpeed;
  int framesTotal;
  int direction;

 public:
  Character(b2World *world);
  void Update();
  void Draw();
  Vector2 getPosition();
  Vector2 getVelocity();

 private:
  void Init();
  void Controls();
  void AnimationUpdate();
  void AnimationDraw();
  void LoadTextures();
  void IdleAnimation();
};