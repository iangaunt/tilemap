#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#include "h/ball.h"
#include "h/resource_dir.h"
#include "h/tile.h"

int main() {
    srand(time(NULL));

    const Color darkGreen = {20, 160, 133, 255};

    SearchAndSetResourceDir("resources");
    
    constexpr int width = 1152;
    constexpr int height = 1152;
    
    Ball ball;
	
    InitWindow(width, height, "test");
    SetTargetFPS(60);

    Image forest = LoadImage("forest_tilemap.png");
    Tile* forest_left_corner = new Tile(forest, "forest_left_corner");
    
    ImageCrop(&forest, {0, 0, 24, 24});
    ImageResize(&forest, 72, 72);

    Texture2D texture = LoadTextureFromImage(forest);
    UnloadImage(forest);
    
    while (!WindowShouldClose()) {
        ball.Update();
        
        BeginDrawing();
            ClearBackground(darkGreen);
            ball.Draw();
        EndDrawing();

        DrawText("Hello Raylib", 200, 200, 20, WHITE);
		DrawTexture(texture, 0, 0, WHITE);
    }

    UnloadTexture(texture);
    CloseWindow();
}