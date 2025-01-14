#include "./h/tilemap.h"
#include "./h/tile.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include <raylib.h>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::unordered_map;

TileMap::TileMap() {
    map = {};
}

bool TileMap::ContainsKey(string elem) {
    auto f = map.find(elem);
    return f != map.end();
}

bool TileMap::LoadTiles(const char* image_file, const char* name_file, int width, int height) {
    ifstream names(name_file);
    string str;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::getline(names, str);
            Tile* t;

            if (ContainsKey(str)) {
                t = map.at(str);
                t->AddImage(image_file, j * 24, i * 24);
            } else {
                t = new Tile(image_file, str, j * 24, i * 24);
                std::pair<string, Tile*> pair (str, t);
                map.insert(pair);
            }
        }
    }

    return true;
}

Texture2D TileMap::DisplayMap(const char* file) {
    ifstream tiles(file);
    string str;

    Image bg = LoadImage("forest_tilemap.png");
    ImageResize(&bg, 1152, 1152);

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            std::getline(tiles, str);
            cout << str << endl;

            Tile* t = map.at(str);
            t->TileDraw(bg, 72 * i, 72 * j);
        }
    }

    Texture2D tex = LoadTextureFromImage(bg);
    UnloadImage(bg); 
    return tex;
}