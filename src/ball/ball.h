#pragma once

class Ball {
 private:
  int x;
  int y;
  int prevX;
  int prevY;
  int speedX;
  int speedY;
  int deformationSpeed;
  int minRadius;
  int initialRadius;
  int radiusX;
  int radiusY;

 public:
  Ball();
  void Update();
  void Draw();

 private:
  void Deformation();
  void Controls();
};