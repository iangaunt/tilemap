#ifndef TILEMAP_H
#define TILEMAP_H

#include <string>
#include <unordered_map>

#include "tile.h"

class TileMap {
    public:
        TileMap(int screen_width, int screen_height);

        int width;
        int height;

        std::unordered_map<std::string, Tile*> map;

        bool LoadTiles(const char* image_file, const char* name_file, int width, int height);
        Texture2D DisplayMap(const char* file);
        bool ContainsKey(std::string elem);

        int FetchWallmask(const char* image_file, int x, int y);
        void LoadMaskedTiles(const char* image_file);
};

#endif