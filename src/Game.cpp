#include <iostream>
#include <vector>
#include "Game.h"
#include "Projectile.h"
#include "config.h"

GameState::GameState() : player(SCREEN_WIDTH / 2, SCREEN_HEIGHT + player.size.y), isGameOver(false) {}

void GameState::SpawnProjectile(Projectile projectile) {
  projectiles.emplace_back(projectile);
}

void GameState::SpawnEnemy(Enemy enemy) {
  enemies.emplace_back(enemy);
}

void GameState::Update(float dt) {
  if (player.hp <= 0) {
    isGameOver = true;
    return;
  }
  
  // Player
  player.Update(dt);

  // Projectiles
  projectiles.erase(
    std::remove_if(projectiles.begin(), projectiles.end(), [](const Projectile& p){
        return !p.isActive;
    }),
    projectiles.end()
  );
  
  for (auto& p :projectiles) { p.Update(dt); }

  // Enemies
  enemies.erase(
    std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e){
        return !e.isAlive;
    }),
    enemies.end()
  );
  
  for (auto& e : enemies) { e.Update(dt); }

  // Colision Projectile X Enemy
  for (auto& p : projectiles) {
    for (auto& e : enemies) {
      Rectangle enemyRec = { e.position.x, e.position.y, e.size.x, e.size.y };

      if (CheckCollisionCircleRec(p.position, p.radius, enemyRec)) {
        if (p.owner == PLAYER)
        {
          p.isActive = false;
          e.hp -= p.damage;
        }
        
      }
    }

    // Colision Player X Enemy Projectile
    Rectangle playerRec = { 
      player.position.x,
      player.position.y,
      player.size.x,
      player.size.y 
    };

    if (CheckCollisionCircleRec(p.position, p.radius, playerRec)) {
      if (p.owner == ENEMY)
      {
        p.isActive = false;
        player.hp -= p.damage;
      }
      
    }
  }
}

void GameState::Draw() const {
  BeginDrawing();
  ClearBackground(DARKGRAY);
  
  // Debug
  DrawFPS(SCREEN_WIDTH - 100, 20);
  DrawRectangle(20, 20, (player.hp / player.hpMax) * 100, 20, RED);
  DrawRectangleLines(20, 20, 100, 20, WHITE);

  // Player
  player.Draw();

  // Projectiles
  for (auto& p : projectiles) { p.Draw(); }

  // Enemies
  for (auto& e : enemies) { e.Draw(); }

  EndDrawing();
}