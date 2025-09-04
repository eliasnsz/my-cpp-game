#include "Player.h"

#include <iostream>
#include <raylib.h>

#include "config.h"
#include "Projectile.h"
#include "Game.h"

Player::Player(float posX, float posY) : 
    position({ posX, posY }), 
    velocity({ 300.0f, 0.0f }),
    size({ 40.0f, 40.0f }),
    attackSpeed(0.85),
    jumpHeigth(480.0f),
    isGrounded(false),
    canShoot(true),
    lastShootTime(GetTime() - 1 / attackSpeed) {}
    
Vector2 Player::GetCenter() {
    return { position.x + size.x / 2.0f, position.y + size.y / 2.0f };
}
    
void Player::MoveRight() {
    position.x += velocity.x * GetFrameTime();

    if(position.x + size.x > SCREEN_WIDTH) {
        position.x = SCREEN_WIDTH - size.x;
    }
}

void Player::MoveLeft() {
    position.x -= velocity.x * GetFrameTime();
        
    if(position.x <= 0) {
        position.x = 0;
    }
}

void Player::Jump() {
    if(isGrounded) {
        velocity.y -= jumpHeigth;
    }
}

void Player::Shoot(GameState& game) {
    if(!canShoot) {
        return;
    }
    
    Vector2 sourcePos = { position.x + (size.x / 2), position.y };
    Vector2 mousePos = GetMousePosition();
    Vector2 direction = { sourcePos.x - mousePos.x, sourcePos.y - mousePos.y };

    float projectileSpeed = 400.0f;

    Projectile projectile(sourcePos, direction, projectileSpeed, Owner::PLAYER);
    
    game.SpawnProjectile(projectile);
    lastShootTime = GetTime();
}

void Player::ApplyPhysics() {
    velocity.y += GRAVITY * GetFrameTime();
    position.y += velocity.y * GetFrameTime();
}

void Player::CheckGroundColision() {
    if (position.y + size.y >= SCREEN_HEIGHT) { 
        position.y = SCREEN_HEIGHT - size.y;
        velocity.y = 0;
        isGrounded = true;
    } else {
        isGrounded = false;
    }
}

void Player::Update(float dt) {
    ApplyPhysics();
    CheckGroundColision();
    canShoot = GetTime() - lastShootTime >= 1 / attackSpeed;
}

void Player::Draw() const {
    DrawRectangleV(position, size, WHITE);
}