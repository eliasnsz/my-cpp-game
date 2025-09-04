#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <raylib.h>

enum Owner { PLAYER, ENEMY };

class Projectile {
    public:
        Vector2 position;
        Vector2 direction;
        Owner owner;
        float speed;
        float radius;
        bool isActive;

        Projectile(float posX, float posY, float speed, Owner owner);

        void Update(float dt);
        void Draw() const;
};

#endif