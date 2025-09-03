#include <iostream>
#include <raylib.h>
#include <math.h>
#include <vector>
#include <algorithm>

#include "game.cpp"
#include "player.cpp"
#include "projectile.cpp"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Xerath First Stand");
    SetTargetFPS(144);
    
    Player player(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 40);

    while(!WindowShouldClose()) {
        // Logic
        player.update();
        
        for (size_t i = 0; i < player.projectiles.size(); i++)
        {
            player.projectiles[i].update();
        }
        
        
        // Drawing
        BeginDrawing();
            // DEBUG INFO
            DrawText(std::to_string(player.position.x).c_str(), 40, 40, 20, WHITE);
            DrawText(std::to_string(player.position.y).c_str(), 40, 70, 20, WHITE);
            DrawText(std::to_string(player.velocity.x).c_str(), 40, 100, 20, WHITE);
            DrawText(std::to_string(player.velocity.y).c_str(), 40, 130, 20, WHITE);
            DrawText(std::to_string(player.isGrounded).c_str(), 40, 160, 20, WHITE);
            DrawText(std::to_string(player.projectiles.size()).c_str(), 40, 190, 20, WHITE);
            
            ClearBackground(DARKGRAY);
            player.draw();

            for (size_t i = 0; i < player.projectiles.size(); i++)
            {
                player.projectiles[i].draw();
                player.projectiles.erase(std::remove_if(player.projectiles.begin(), player.projectiles.end(), 
                                 [](Projectile p){ return p.isActive == false; }),
                  player.projectiles.end());
            }
            
        EndDrawing();
    }

    CloseWindow();
}