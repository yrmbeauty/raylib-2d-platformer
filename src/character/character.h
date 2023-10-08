#pragma once

#include <raylib.h>

#include "../../libs/physac.h"

struct CharacterTextures {
  Texture2D idle;
  Texture2D run;
  Texture2D jump;
};

class Character {
private:
  Rectangle frameRec{};
  CharacterTextures characterTextures{};
  Texture2D currentTexture{};
  PhysicsBody body{};
  int currentFrame;
  int framesCounter;
  int framesSpeed;
  float direction;

public:
  Character();
  void Update();
  void Draw();

private:
  void Init();
  void Controls();
  void AnimationUpdate();
  void AnimationDraw();
  void LoadTextures();
  void IdleAnimation();
};