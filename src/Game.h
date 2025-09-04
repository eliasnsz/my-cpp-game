#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include <vector>
#include <algorithm>

class GameState {
  public:
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Projectile> projectiles;
    bool isGameOver;
  
    GameState();

    void SpawnEnemy(Enemy enemy);
    void SpawnProjectile(Projectile projectile);

    void Update(float dt);
    void Draw() const;
};

#endif