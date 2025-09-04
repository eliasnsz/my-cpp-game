#include "Projectile.h"
#include "config.h"
#include <math.h>

Projectile::Projectile(float posX, float posY, float speed, Owner owner)
 : position({ posX, posY}), speed(speed), radius(6.0f), isActive(true), owner(owner) {
  
  Vector2 mousePos = GetMousePosition();

  Vector2 dir = {
      dir.x = position.x - mousePos.x,
      dir.y = position.y - mousePos.y,
  };

  float vectorLength = std::sqrt(dir.x * dir.x + dir.y * dir.y);

  if (vectorLength != 0 )
  {
    direction = { dir.x / vectorLength, dir.y / vectorLength };
  } else {
    direction = { 0, 0 };
  }
}

void Projectile::Update(float dt) {
  position.x -= speed * direction.x * dt;
  position.y -= speed * direction.y * dt;

  bool isOutOfBoundaries = (
    position.x + radius < 0 || position.x - radius > SCREEN_WIDTH ||
    position.y + radius < 0 || position.y - radius > SCREEN_HEIGHT
  );

  if (isOutOfBoundaries) {
    isActive = false;
  }
}

void Projectile::Draw() const {
  Color color;
  
  if (owner == PLAYER) {
    color = WHITE;
  }

  if (owner == ENEMY) {
    color = RED;
  }
  
  DrawCircleV(position, radius, color);
}
