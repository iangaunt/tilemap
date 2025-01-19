#include <string>
#include <iostream>

#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#include "./h/ball.h"
#include "./h/mapgen.h"
#include "./h/resource_dir.h"
#include "./h/tile.h"
#include "./h/tilemap.h"

int WIDTH = 50;
int HEIGHT = 30;

int SCREEN_WIDTH = WIDTH * 72;
int SCREEN_HEIGHT = HEIGHT * 72;

int main() {
    srand(time(NULL));

    const Color darkGreen = {20, 160, 133, 255};

    SearchAndSetResourceDir("resources");

    Ball ball;
	
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "test");
    SetTargetFPS(60);

    TileMap* ex = new TileMap(WIDTH, HEIGHT);
    ex->LoadTiles("dummy_tiles.png", "dummy_tiles.txt", 6, 1);

    MapGen* map = new MapGen(WIDTH, HEIGHT);
    map->GenerateMap(3, 2);
    map->WriteTo("dummy.txt");

    Texture2D tex = ex->DisplayMap("dummy.txt");
    
    while (!WindowShouldClose()) {
        ball.Update();
        
        BeginDrawing();
            ClearBackground(darkGreen);
            ball.Draw();
        EndDrawing();

        DrawTexture(tex, 0, 0, WHITE);
    }

    CloseWindow();
}