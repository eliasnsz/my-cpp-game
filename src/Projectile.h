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

        Projectile(Vector2 position, Vector2 direction, float speed, Owner owner);

        
        void Update(float dt);
        void Draw() const;

    private:
        Vector2 Normalize(Vector2 v);
};

#endif