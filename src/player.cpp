#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <raylib.h>
#include <vector>

#include "game.cpp"
#include "projectile.cpp"

class Player {
    private: 
        float _lastShootTime;
    public: 
        Vector2 position;
        Vector2 velocity;
        Vector2 size;
        float jumpHeigth;
        bool isGrounded;
        bool canShoot;
        float attackSpeed;
        std::vector<Projectile> projectiles;

    Player(float x, float y) {
        position = { x, y };
        velocity = { 300.0f, 0.0f };
        size = { 40.0f, 40.0f };
        jumpHeigth = 480.0f;
        isGrounded = false;
        projectiles = {};
        canShoot = true;
        attackSpeed = 0.85;
        _lastShootTime = GetTime() - 1 / attackSpeed;
    }

    
    void applyPhysics() {
        velocity.y += GRAVITY * GetFrameTime();
        position.y += velocity.y * GetFrameTime();
    }

    void checkGroundColision() {
        if (position.y + size.y >= SCREEN_HEIGHT) { 
            position.y = SCREEN_HEIGHT - size.y;
            velocity.y = 0;
            isGrounded = true;
        }
    }

    void jump() {
        if(isGrounded) {
            velocity.y -= jumpHeigth;
            isGrounded = false;
        }
    }

    void moveRight() {
        position.x += velocity.x * GetFrameTime();

        if(position.x + size.x > SCREEN_WIDTH) {
            position.x = SCREEN_WIDTH - size.x;
        }
    }

    void moveLeft() {
        position.x -= velocity.x * GetFrameTime();
        
        if(position.x <= 0) {
            position.x = 0;
        }
    }

    void shoot() {
        if(!canShoot) {
            return;
        }
        
        Vector2 direction = GetMousePosition();
        Vector2 startPos = {
            startPos.x = position.x + (size.x / 2),
            startPos.y = position.y
        };

        Projectile projectile(startPos.x, startPos.y, 400);
        projectiles.emplace_back(projectile);
        attackSpeed *= 1.03;
        _lastShootTime = GetTime();
    }

    void update() {
        applyPhysics();
        checkGroundColision();
        canShoot = GetTime() - _lastShootTime >= 1 / attackSpeed;
        
        if(IsKeyDown(KEY_RIGHT)) { 
            moveRight();
        };

        if(IsKeyDown(KEY_LEFT)) { 
            moveLeft();
        }

        if(IsKeyDown(KEY_UP)) { 
            jump();
        }

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { 
            shoot();
        }   
    }

    void draw() {
        DrawRectangleV(position, size, WHITE);
    }
};

#endif