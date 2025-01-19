#include "./h/tile.h"

#include <string>
#include <vector>

#include <raylib.h>
#include <stdlib.h>
#include <time.h>

using std::string;
using std::vector;

Tile::Tile() {
    textures = new vector<Image>();
}

Tile::Tile(const char* file, string nameh) {
    textures = new vector<Image>();
    name = nameh;
    
    Image image = LoadImage(file);
    ImageCrop(&image, {0, 0, 24, 24});
    textures->push_back(image);
}

Tile::Tile(const char* file, string nameh, int x, int y) {
    textures = new vector<Image>();
    name = nameh;

    Image image = LoadImage(file);
    ImageCrop(&image, {(float) x, (float) y, 24, 24});
    textures->push_back(image);
}

void Tile::TileDraw(Image img, int x, int y) {
    int r = rand() % textures->size();
    ImageDraw(&img, textures->at(r), {0, 0, 24, 24}, {(float) x, (float) y, 24, 24}, WHITE);
}

void Tile::TileDraw(Image img, int x, int y, int index) {
    ImageDraw(&img, textures->at(index), {0, 0, 24, 24}, {(float) x, (float) y, 24, 24}, WHITE);
}

void Tile::AddImage(const char* file, int x, int y) {
    Image image = LoadImage(file);
    ImageCrop(&image, {(float) x, (float) y, 24, 24});
    textures->push_back(image);
}

Tile::~Tile() {
    for (int i = 0; i < (int) (textures->size()); i++) {
        UnloadImage(textures->at(i));
    }
}