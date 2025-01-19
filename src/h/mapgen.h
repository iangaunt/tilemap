#ifndef MAPGEN_H
#define MAPGEN_H

#include <raylib.h>
#include <string>
#include <vector>

class MapGen {
    public:
        MapGen(int width, int height);

        int width;
        int height;
        int* positions;

        void GenerateMap(int m, int n);
        void WriteTo(const char* file);
};

#endif