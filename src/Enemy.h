#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>
#include "config.h"

class GameState;

enum EnemyState {
    CHASE,
    ATTACK
};

class Enemy {
    public: 
        float hp;
        float hpMax;
        float baseDamage;
        float damageMultiplier;
        Vector2 position;
        Vector2 velocity;
        Vector2 size;
        EnemyState state;
        bool isAlive;
        float rotate;
        float attackSpeed;
        
        Enemy(float x, float y);
        
        Vector2 GetCenter() const;
        void Shoot(GameState& game);
        void Chase(Vector2 playerPosition);
        void UpdateEnemyAI(GameState& game);
        
        void Update(float dt);
        void Draw() const;
        
    private:
        bool canShoot;
        float lastShootTime;
};

#endif