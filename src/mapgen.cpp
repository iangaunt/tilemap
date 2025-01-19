#include "./h/mapgen.h"

#include <fstream>
#include <iostream>
#include <vector>

#include <stdlib.h>
#include <time.h>

using std::ofstream;
using std::vector;

MapGen::MapGen(int width, int height) {
    this->width = width;
    this->height = height;

    positions = new int[width * height];
    for (int i = 0; i < width * height; i++) {
        positions[i] = 0;
    }
}

void MapGen::GenerateMap(int m, int n) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (i == 0 || j == 0 || i == width - 1 || j == height - 1) {
                positions[i * height + j] = 5;
            }
        }
    }

    int m_cut = width / m;
    int n_cut = height / n;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            DrawLine(i * m_cut * 72, j * n_cut * 72, (i + 1) * m_cut * 72, (j + 1) * n_cut * 72, RED);

            int upper_x = m_cut * (i + 1);
            int lower_x = upper_x - m_cut;
            if (i != 0) lower_x++;

            int upper_y = n_cut * (j + 1);
            int lower_y = upper_y - n_cut;
            if (j != 0) lower_y++;

            int x = lower_x + 2 + rand() % (upper_x - lower_x - 4);
            int y = lower_y + 2 + rand() % (upper_y - lower_y - 4);

            int room_width = rand() % 4 + 7;
            if (room_width % 2 == 0) room_width--;

            int room_height = rand() % 4 + 7;
            if (room_height % 2 == 0) room_height--;

            bool yellow_generated = false;
            int chance = room_width * room_height;

            for (int w = 0; w < room_width; w++) {
                for (int h = 0; h < room_height; h++) {
                    int pos = (x + (w - room_width / 2)) * height + (y + (h - room_height / 2));
                    if (positions[pos] != 5) positions[pos] = 1;

                    if (rand() % chance == 0 && !yellow_generated) {
                        positions[pos] = 3;
                        yellow_generated = true;
                    } 
                    chance--;
                }
            }
        }
    }
}

void MapGen::WriteTo(const char* file) {
    ofstream myfile;
    myfile.open(file);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            switch (positions[i * height + j]) {
                case 0: { myfile << "black\n"; break; }
                case 1: { myfile << "white\n"; break; }
                case 2: { myfile << "blue\n"; break; }
                case 3: { myfile << "yellow\n"; break; }
                case 4: { myfile << "red\n"; break; }
                case 5: { myfile << "green\n"; break; }

                default: {
                    break;
                }
            }
        }
    }

    myfile.close();
}

