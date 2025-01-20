#include "./h/maps/room.h"

#include <iostream>

#include <raylib.h>
#include <stdlib.h>

/**
 * Creates a new `Room` object with a specified `width`, `height`,
 * and top-left corner represented by the point `(x, y)`.
 */
Room::Room(int width, int height, int x, int y) {
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
}

/**
 * Selects a random wall tile from the rectangle and
 * returns it in the form `[x, y]`.
 * 
 * @return A two-integer array containing the wall tile coordinates.
 */
int* Room::SelectWallTile() {
    int* tile1 = new int[2];
    int* tile2 = new int[2];

    tile1[0] = rand() % 2 == 0 ? x : x + width - 1;
    tile1[1] = y + rand() % (height - 1);

    tile2[0] = x + rand() % (width - 1);
    tile2[1] = rand() % 2 == 0 ? y : y + height - 1;

    return rand() % 2 == 0 ? tile1 : tile2;
}

void Room::PathTo(int w, int h, int* positions, int* other) {
    int* start = SelectWallTile();

    int dx = other[0] - start[0];
    int dy = other[1] - start[1];

    int xstep = dx < 0 ? -1 : 1;
    int ystep = dy < 0 ? -1 : 1;

    int mx = 0;
    int my = 0;

    while (mx != dx || my != dy) {
        int step = rand() % 2;

        if (mx == dx) step = 1;
        if (my == dy) step = 0;

        if (step == 0) {
            mx += xstep;
            positions[(start[0] + mx) * h + (start[1] + my)] = 1; 
        } else {
            my += ystep;
            positions[(start[0] + mx) * h + (start[1] + my)] = 1; 
        }
    }
    
    return;
}