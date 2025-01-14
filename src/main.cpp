#include <string>
#include <iostream>

#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#include "./h/ball.h"
#include "./h/resource_dir.h"
#include "./h/tile.h"
#include "./h/tilemap.h"

int width = 1152;
int height = 1152;

int main() {
    srand(time(NULL));

    const Color darkGreen = {20, 160, 133, 255};

    SearchAndSetResourceDir("resources");

    Ball ball;
	
    InitWindow(width, height, "test");
    SetTargetFPS(60);

    TileMap* forest = new TileMap();
    forest->LoadTiles("forest_tilemap.png", "forest_tilemap.txt", 7, 6);
    Texture2D forest_texture = forest->DisplayMap("forest.txt");
    
    while (!WindowShouldClose()) {
        ball.Update();
        
        BeginDrawing();
            ClearBackground(darkGreen);
            ball.Draw();
        EndDrawing();

        DrawTexture(forest_texture, 0, 0, WHITE);
    }

    CloseWindow();
}