#ifndef TILE_H
#define TILE_H

#include <raylib.h>
#include <string>
#include <vector>

class Tile {
    public:
        Tile();
        Tile(const char* file, std::string nameh);
        Tile(const char* file, std::string nameh, int x, int y);
        ~Tile();

        std::vector<Image>* textures;
        std::string name;
        int wallmask;

        void TileDraw(Image img, int x, int y);
        void TileDraw(Image img, int x, int y, int index);
        void AddImage(const char* file, int x, int y);
};

#endif