#ifndef ENEMY_H
#define ENEMY_H

#include <raylib.h>
#include "config.h"

class GameState;

class Enemy {
    public: 
        Vector2 position;
        Vector2 velocity;
        Vector2 size;
        float attackSpeed;
        
        Enemy(float x, float y);
        
        void Shoot(GameState& game);
        
        void Update(float dt);
        void Draw() const;
        
    private:
        bool canShoot;
        float lastShootTime;
};

#endif