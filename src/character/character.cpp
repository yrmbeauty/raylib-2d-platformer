#include "character.hpp"

#include <box2d/box2d.h>
#include <raylib.h>

#include <constants.hpp>

#define VELOCITY 60.0f

Character::Character(b2World *world) {
  currentFrame = 0;
  framesCounter = 0;
  framesSpeed = 8;
  direction = 1;

  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();

  bodyX = screenWidth / 2;
  bodyY = screenHeight / 2;
  bodyWidth = 3.0f;
  bodyHeight = 3.0f;

  this->world = world;

  Init();
}

void Character::Init() {
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.fixedRotation = true;
  bodyDef.position.Set(bodyX, bodyY);
  body = world->CreateBody(&bodyDef);

  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(bodyWidth * 0.5, bodyHeight * 0.7);
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 100.0f;
  body->CreateFixture(&fixtureDef);
  body->SetGravityScale(2);

  LoadTextures();
}

void Character::Update() {
  Controls();
  AnimationUpdate();
}

void Character::Draw() { AnimationDraw(); }

void Character::LoadTextures() {
  Texture2D idle =
      LoadTexture(Constants::GetAssetPath("character/Idle.png").c_str());
  Texture2D run =
      LoadTexture(Constants::GetAssetPath("character/Run.png").c_str());
  Texture2D jump =
      LoadTexture(Constants::GetAssetPath("character/Jump.png").c_str());

  characterTextures = {idle, run, jump};
}

void Character::Controls() {
  b2Vec2 velocity = body->GetLinearVelocity();

  if (IsKeyDown(KEY_LEFT)) {
    direction = -1;
    velocity.x = -VELOCITY;
  } else if (IsKeyDown(KEY_RIGHT)) {
    direction = 1;
    velocity.x = VELOCITY;
  }

  if (IsKeyPressed(KEY_UP)) {
    velocity.y = -VELOCITY;
  }

  body->SetLinearVelocity(velocity);
}

void Character::AnimationUpdate() {
  auto [idle, run, jump] = characterTextures;
  b2Vec2 velocity = body->GetLinearVelocity();
  bool isGrounded = velocity.y == 0;

  if (!isGrounded) {
    currentTexture = jump;
    frameRec.width = direction * (float)jump.width / 3;
    frameRec.height = (float)jump.height;

    if (velocity.y < -30) {
      frameRec.x = (float)jump.width;
    } else if (velocity.y < 30) {
      frameRec.x = (float)jump.width / 3;
    } else {
      frameRec.x = 2 * (float)jump.width / 3;
    }
  }

  if (isGrounded && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
    currentTexture = idle;
    framesTotal = 10;
    frameRec.width = direction * (float)idle.width / framesTotal;
    frameRec.height = (float)idle.height;
    IdleAnimation();
  }

  if (isGrounded && (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT))) {
    currentTexture = run;
    framesTotal = 8;
    frameRec.width = direction * (float)run.width / framesTotal;
    frameRec.height = (float)run.height;
    IdleAnimation();
  }
}

void Character::AnimationDraw() {
  b2Vec2 position = body->GetPosition();

  Rectangle dest = {position.x - bodyWidth, position.y - bodyHeight,
                    bodyWidth * 2, bodyHeight * 2};
  Vector2 origin = {0, 0};
  float rotation = 0;
  DrawTexturePro(currentTexture, frameRec, dest, origin, rotation, WHITE);
}

void Character::IdleAnimation() {
  framesCounter++;

  if (framesCounter >= (60 / framesSpeed)) {
    framesCounter = 0;
    currentFrame++;

    if (currentFrame > framesTotal - 1)
      currentFrame = 0;

    frameRec.x = (float)currentFrame * currentTexture.width / framesTotal;
  }
}

Vector2 Character::getPosition() {
  b2Vec2 position = body->GetPosition();
  return (Vector2){position.x, position.y};
}

Vector2 Character::getVelocity() {
  b2Vec2 velocity = body->GetLinearVelocity();
  return (Vector2){velocity.x, velocity.y};
}