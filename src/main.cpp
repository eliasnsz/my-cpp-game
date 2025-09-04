#include <iostream>
#include <raylib.h>
#include <math.h>
#include <vector>
#include <algorithm>

#include "config.h"
#include "Game.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Xerath First Stand");
    SetTargetFPS(144);
    
    GameState game;

    while(!WindowShouldClose()) {
        if(IsKeyDown(KEY_D)) { 
            game.player.MoveRight();
        };

        if(IsKeyDown(KEY_A)) { 
            game.player.MoveLeft();
        }

        if(IsKeyDown(KEY_W)) { 
            game.player.Jump();
        }

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { 
            game.player.Shoot(game);
        }   
        
        float dt = GetFrameTime();
        
        game.Update(dt);
        game.Draw();
    }

    CloseWindow();
}