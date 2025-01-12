#include "../h/tile.h"

#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Tile::Tile(Image imageh, std::string nameh) {
    name = nameh;
    
    ImageCrop(&imageh, {0, 0, 24, 24});
    ImageResize(&imageh, 72, 72);
    image = LoadTextureFromImage(imageh);
    AddLocation(0, 0);
}

Tile::Tile(Image imageh, std::string nameh, int x, int y) {
    name = nameh;

    ImageCrop(&imageh, {(float) x, (float) y, (float) x + 24, (float) y + 24});
    ImageResize(&imageh, 72, 72);
    image = LoadTextureFromImage(imageh);
    AddLocation(x, y);
}

void Tile::TileDraw(int x, int y) {
    int index = rand() % locations.size();

    DrawTexture(
        image, 
        locations.at(index)->x, 
        locations.at(index)->y, 
        WHITE
    );
}

void Tile::TileDraw(int x, int y, int index) {
    DrawTexture(
        image, 
        locations.at(index)->x, 
        locations.at(index)->y, 
        WHITE
    );
}

void Tile::AddLocation(int x, int y) {
    locations.push_back(new TileLocation(x, y));
}