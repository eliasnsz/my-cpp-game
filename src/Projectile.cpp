#include "Projectile.h"
#include "config.h"
#include <math.h>

Projectile::Projectile(Vector2 position, Vector2 direction, float speed, float damage, Owner owner) : 
  position(position), 
  direction(Normalize(direction)), 
  speed(speed), 
  damage(damage), 
  radius(6.0f), 
  isActive(true), 
  owner(owner) {}

Vector2 Projectile::Normalize(Vector2 v) {
  Vector2 direction;
  
  float vectorLength = std::sqrt(v.x * v.x + v.y * v.y);

  if (vectorLength != 0 )
  {
    direction = { v.x / vectorLength, v.y / vectorLength };
  } else {
    direction = { 0, 0 };
  }

  return direction;
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
