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

        int* GenerateRoomSize();
        int* GenerateRoomPos(int rw, int rh, int m_cut, int n_cut, int i, int j);
        int GetMaskFromPosition(int x, int y);

        void WriteTo(const char* file);
        void ClearFile(const char* file);
};

#endif