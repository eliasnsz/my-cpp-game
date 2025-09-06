#include "Enemy.h"

#include <iostream>
#include <math.h>
#include <raylib.h>
#include <raymath.h>

#include "config.h"
#include "Projectile.h"
#include "Game.h"

Enemy::Enemy(float posX, float posY) : 
    hp(20.0f), 
    hpMax(20.0f), 
    baseDamage(4.0f),
    damageMultiplier(1.0f),
    position({ posX, posY }), 
    velocity({ 300.0f, 150.0f }),
    isAlive(true),
    state(ATTACK),
    size({ 40.0f, 40.0f }),
    attackSpeed(0.65),
    canShoot(true),
    lastShootTime(GetTime() - 1 / attackSpeed) {}

Vector2 Enemy::GetCenter() const {
    return { position.x + (size.x / 2.0f), position.y + (size.y / 2.0f) };
}
    
void Enemy::Shoot(GameState& game) {
    if(!canShoot) {
        return;
    }
    
    Vector2 sourcePos = GetCenter();
    Vector2 playerPos = game.player.GetCenter();
    Vector2 direction = Vector2Subtract(sourcePos, playerPos);

    float projectileSpeed = 300.0f;
    float projectileDamage = baseDamage * damageMultiplier;

    Projectile projectile(sourcePos, direction, projectileSpeed, projectileDamage, Owner::ENEMY);
    
    game.SpawnProjectile(projectile);
    lastShootTime = GetTime();
}

void Enemy::UpdateEnemyAI(GameState& game) {
    float distance = Vector2Distance(position, game.player.position);

    if(distance > 500) {
        state = CHASE;
    } else {
        state = ATTACK;
    }

    switch (state) {
    case CHASE:
        Chase(game.player.position);
        break;
    
    case ATTACK:
        Shoot(game);
        velocity.x = 0;
        velocity.y = 0;
        break;
        
    default:
        break;
    }
}

void Enemy::Chase(Vector2 playerPosition) {
    if (velocity.x < 300.0f) { velocity.x += 25.0f; }
    if (velocity.y < 150.0f) { velocity.y += 25.0f; }

    Vector2 direction = Vector2Normalize(Vector2Subtract(position, playerPosition));
    
    position.x -= velocity.x * direction.x * GetFrameTime();
    position.y -= velocity.y * direction.y * GetFrameTime();
}

void Enemy::Update(float dt) {
    canShoot = GetTime() - lastShootTime >= 1 / attackSpeed;

    if (hp <= 0) {
        isAlive = false;
    }
    
}

void Enemy::Draw() const {
    Rectangle enemyRect = {
        x: position.x,
        y: position.y,
        width: size.x,
        height: size.y
    };

    float hpPercent = hp / hpMax;
    
    const unsigned char minAlpha = 100;
    const unsigned char maxAlpha = 255;

    // interpola entre min e max
    unsigned char alpha = (unsigned char)(minAlpha + hpPercent * (maxAlpha - minAlpha));

    Color color = { 255, 0, 0, alpha };

    // largura proporcional ao HP
    int barWidth = (int)(100 * hpPercent);
    
    DrawRectangleRec(enemyRect, color);
}