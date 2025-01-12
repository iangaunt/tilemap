#ifndef TILE_H
#define TILE_H

#include <raylib.h>
#include <string>
#include <vector>

#include "tile_location.h"

class Tile {
    public:
        Tile(Image imageh, std::string nameh);
        Tile(Image imageh, std::string nameh, int x, int y);

        Texture2D image;
        std::string name;
        std::vector<TileLocation*> locations;

        void TileDraw(int x, int y);
        void TileDraw(int x, int y, int index);
        void AddLocation(int x, int y);
};

#endif