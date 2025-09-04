#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "config.h"

class GameState;

class Player {
    public: 
        Vector2 position;
        Vector2 velocity;
        Vector2 size;
        float jumpHeigth;
        float attackSpeed;
        
        Player(float x, float y);
        
        Vector2 GetCenter();
        void MoveRight();
        void MoveLeft();
        void Jump();
        void Shoot(GameState& game);
        
        void Update(float dt);
        void Draw() const;
        
    private:
        bool canShoot;
        bool isGrounded;
        float lastShootTime;
        void ApplyPhysics();
        void CheckGroundColision();
};

#endif