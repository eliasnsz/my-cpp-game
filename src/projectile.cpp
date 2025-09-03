#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <iostream>
#include <raylib.h>
#include <vector>
#include <math.h>

#include "game.cpp"

class Projectile {
    public:
        Vector2 position;
        Vector2 direction;
        float _speed;
        float radius;
        bool isActive;

    Projectile(float posX, float posY, float speed) {
        radius = 6;
        isActive = true;
        position = { posX, posY };
        _speed = speed;

        Vector2 mousePos = GetMousePosition();

        Vector2 dir = {
            dir.x = position.x - mousePos.x,
            dir.y = position.y - mousePos.y,
        };

        float vectorLength = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        direction = {
            direction.x = dir.x / vectorLength,
            direction.x = dir.y / vectorLength,
        };
    }

    void update() {
        position.x -= _speed * direction.x * GetFrameTime();
        position.y -= _speed * direction.y * GetFrameTime();

        bool isOutOfBoundaries = (
            position.x + radius < 0 || position.x - radius > SCREEN_WIDTH ||
            position.y + radius < 0 || position.y - radius > SCREEN_HEIGHT
        );

        if (isOutOfBoundaries) {
            isActive = false;
        }
    }
    
    void draw() {
        DrawCircleV(position, radius, WHITE);
    }
};

#endif