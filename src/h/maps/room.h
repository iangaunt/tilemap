#ifndef ROOM_H
#define ROOM_H

#include <raylib.h>

class Room {
    public:
        Room(int width, int height, int x, int y);

        int width;
        int height;
        int x;
        int y;

        int* SelectWallTile();
        void PathTo(int w, int h, int* positions, int* other);
};

#endif