#include <chrono>
#include <string>
#include <iostream>

#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#include "./h/maps/mapgen.h"
#include "./h/resource_dir.h"
#include "./h/tiles/tile.h"
#include "./h/tiles/tilemap.h"

int WIDTH = 50;
int HEIGHT = 30;

int SCREEN_WIDTH = WIDTH * 72;
int SCREEN_HEIGHT = HEIGHT * 72;

using std::chrono::duration;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

int main() {
    srand(time(NULL));
    SearchAndSetResourceDir("resources");
	
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "test");
    SetTargetFPS(60);

    TileMap* walls = new TileMap(WIDTH, HEIGHT);
    // ex->LoadTiles("dummy_tiles.png", "dummy_tiles.txt", 6, 1);
    walls->LoadMaskedTiles("forest_walls.png");
    walls->LoadMaskedTiles("forest_walls_extra.png");

    MapGen* map = new MapGen(WIDTH, HEIGHT);
    map->GenerateMap(3, 2);
    map->WriteTo("dummy.txt");

    Texture2D tex = walls->DisplayMap("dummy.txt");

    // for (const auto& pair : ex->map) {
    //     std::cout << pair.first << " => " << pair.second << std::endl;
    // }
    // std::cout << ex->map.size() << std::endl;

    auto cycle_delay = 5;
	auto last_cycle = high_resolution_clock::now();

    while (!WindowShouldClose()) {
        auto current = high_resolution_clock::now();
	    float delay = duration<float, milliseconds::period>(current - last_cycle).count();

        if (delay >= cycle_delay) {
            BeginDrawing();
                ClearBackground(BLACK);
                DrawTexture(tex, 0, 0, WHITE);
            EndDrawing();
		}
    }

    // map->ClearFile("dummy.txt");

    CloseWindow();
}