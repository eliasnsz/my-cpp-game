#include "Enemy.h"

#include <iostream>
#include <raylib.h>

#include "config.h"
#include "Projectile.h"
#include "Game.h"

Enemy::Enemy(float posX, float posY) : 
    position({ posX, posY }), 
    velocity({ 300.0f, 0.0f }),
    size({ 40.0f, 40.0f }),
    attackSpeed(0.65),
    canShoot(true),
    lastShootTime(GetTime() - 1 / attackSpeed) {}
    
void Enemy::Shoot(GameState& game) {
    if(!canShoot) {
        return;
    }
    
    Player player = game.player;
    
    Vector2 sourcePos = { position.x + (size.x / 2), position.y };
    Vector2 playerPos = { player.position.x + (player.size.x / 2), player.position.y + (player.size.x / 2) };
    Vector2 direction = { sourcePos.x - playerPos.x, sourcePos.y - playerPos.y };

    float projectileSpeed = 300.0f;

    Projectile projectile(sourcePos, direction, projectileSpeed, Owner::ENEMY);
    
    game.SpawnProjectile(projectile);
    lastShootTime = GetTime();
}

void Enemy::Update(float dt) {
    canShoot = GetTime() - lastShootTime >= 1 / attackSpeed;
}

void Enemy::Draw() const {
    DrawRectangleV(position, size, RED);
}