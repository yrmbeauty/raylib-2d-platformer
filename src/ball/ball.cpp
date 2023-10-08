#include "ball.h"

#include <raylib.h>

Ball::Ball() {
  x = 100;
  y = 100;
  prevX = x;
  prevY = y;
  speedX = 2;
  speedY = 2;
  deformationSpeed = speedY;
  minRadius = 35;
  initialRadius = 50;
  radiusX = initialRadius;
  radiusY = initialRadius;
}

void Ball::Update() {
  x += speedX;
  y += speedY;

  this->Deformation();
}

void Ball::Draw() {
  DrawEllipse(x, y, radiusX, radiusY, WHITE);
}

void Ball::Deformation() {
  if ((x >= (GetScreenWidth() - radiusY)) || (x <= radiusY))
    speedX *= -1.0;

  bool inArea = y >= GetScreenHeight() - initialRadius || (y <= radiusY);
  bool isCloserToTop = y < GetScreenHeight() / 2;
  bool isComeCloser = inArea && (isCloserToTop && prevY > y || !isCloserToTop && prevY < y);
  bool isComeOuter = (isCloserToTop && prevY < y || !isCloserToTop && prevY > y);

  if (isComeCloser) {
    radiusY -= deformationSpeed;
  }
  if (isComeOuter && radiusY < initialRadius) {
    radiusY += deformationSpeed;
  }
  if (y >= (GetScreenHeight() - minRadius) || y <= minRadius) {
    speedY *= -1.0;
  }

  prevX = x;
  prevY = y;
}

void Ball::Controls() {
  if (IsKeyPressed(KEY_UP)) {
    speedX *= 1.0;
  }
}