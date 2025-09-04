#include <iostream>
#include <vector>
#include "Game.h"
#include "Projectile.h"
#include "config.h"

GameState::GameState() : player(SCREEN_WIDTH / 2, SCREEN_HEIGHT + player.size.y), isGameOver(false) {}

void GameState::SpawnProjectile(Projectile projectile) {
  projectiles.emplace_back(projectile);
}

void GameState::Update(float dt) {
  // Player
  player.Update(dt);

  // Projectiles
  projectiles.erase(
    std::remove_if(projectiles.begin(), projectiles.end(), [](const Projectile& p){
        return !p.isActive;
    }),
    projectiles.end()
  );
  
  for (size_t i = 0; i < projectiles.size(); i++) {
    projectiles[i].Update(dt);
  }
}

void GameState::Draw() const {
  BeginDrawing();
  ClearBackground(DARKGRAY);
  
  DrawText(std::to_string(projectiles.size()).c_str(), 20, 20, 20, WHITE);

  player.Draw();

  for (size_t i = 0; i < projectiles.size(); i++)
  {
    projectiles[i].Draw();
  }

  EndDrawing();
}