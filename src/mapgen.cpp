#include "./h/maps/mapgen.h"
#include "./h/maps/room.h"

#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>

using std::string;
using std::ofstream;
using std::vector;

/**
 * Creates a new map generator with a specified 
 * `width` and `height` of the screen.
 * 
 * @param width The width of the screen in tiles.
 * @param height The height of the screen in tiles.
 */
MapGen::MapGen(int width, int height) {
    this->width = width;
    this->height = height;

    positions = new int[width * height];
    for (int i = 0; i < width * height; i++) {
        positions[i] = 0;
    }
}

int* MapGen::GenerateRoomSize() {
    // Storage for the dimensions.
    int* dim = new int[2];

    // Generates two random numbers for offset on width and height.
    int rand_width = rand() % 4;
    int rand_height = rand() % 4;

    if (rand_width < 0) rand_width *= -1;
    if (rand_height < 0) rand_height *= -1;

    // Combines the random numbers with a room size constant.
    int room_width = rand_width + 9;
    int room_height = rand_height + 9;

    // Cuts the room into odd dimensions.
    if (room_width % 2 == 0) room_width--;
    if (room_height % 2 == 0) room_height--;

    // Return the room width and height.
    dim[0] = room_width;
    dim[1] = room_height;
    return dim;
}

int* MapGen::GenerateRoomPos(int rw, int rh, int m_cut, int n_cut, int i, int j) {
    // Storage for the dimensions.
    int* pos = new int[2];

    // Generates the upper and lower boundaries for the x coordinate.
    int upper_x = m_cut * (i + 1) + 2;
    int lower_x = upper_x - m_cut - 1;
    upper_x -= rw;

    if (i != 0) lower_x++;

    // Generates the upper and lower boundaries for the y coordinate.
    int upper_y = n_cut * (j + 1) + 2;
    int lower_y = upper_y - n_cut - 1;
    upper_y -= rh;

    if (j != 0) lower_y++;

    // Generates the x and y coordinates.
    int x = lower_x + rand() % (upper_x - lower_x - 1);
    int y = lower_y + rand() % (upper_y - lower_y - 1);

    // Returns the x and y coordinates.
    pos[0] = x;
    pos[1] = y;
    return pos;
}

void MapGen::GenerateMap(int m, int n) {
    // x, y -> x * height + y
    vector<Room*>* rooms = new vector<Room*>();

    // Sets a one-tile radius around the border of the map.
    for (int i = 0; i < width; i++) {
        positions[i * height + 0] = 5;
        positions[i * height + (height - 1)] = 5;
    } 

    for (int i = 0; i < height; i++) {
        positions[0 + i] = 5;
        positions[(width - 1) * height + i] = 5;
    }

    // Divides the screen width and height into m_cut x n_cut chunks.
    int m_cut = width / m;
    int n_cut = height / n;

    // Generates the rooms for the dungeons.
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            /*
             * Defines the width and height of the room to be generated.
             * This is done first to generate the range needed to fit the 
             * room inside of the chunk.
            */
            int* room_dim = GenerateRoomSize();
            int room_width = room_dim[0];
            int room_height = room_dim[1];

            // Defines the position of the room. Rooms are generated from the top-left corner.
            int* room_pos = GenerateRoomPos(room_width, room_height, m_cut, n_cut, i, j);
            int x = room_pos[0];
            int y = room_pos[1];

            // Writes to the file by building the room column by column.
            for (int w = 0; w < room_width; w++) {
                for (int h = 0; h < room_height; h++) {
                    int pos = (x + w) * height + (y + h);
                    if (positions[pos] != 5) positions[pos] = 1;
                }
            }

            Room* r = new Room(room_width, room_height, x, y);
            if (i != 0 || j != 0) {
                Room* other_room = rooms->at(rand() % rooms->size());
                r->PathTo(
                    width, height, 
                    positions, 
                    other_room->SelectWallTile()
                );
            }

            rooms->push_back(r);
        }
    }
}

int MapGen::GetMaskFromPosition(int x, int y) {
    int mask = 0b0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int x_off = x + j;
            int y_off = y + i;

            mask <<= 1;
            if (i == 0 && j == 0) {
                mask |= 1;
                continue;
            }
        
            if (x_off < 0 || x_off >= width || y_off < 0 || y_off >= height) continue;
            if (positions[x_off * height + y_off] == 1) mask |= 1;
        }
    }

    // mask ^= 0b0000000111101111;

    // std::cout << std::bitset<16>(mask) << std::endl;

    return mask;
}

void MapGen::WriteTo(const char* file) {
    ofstream myfile;
    myfile.open(file);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            myfile << std::to_string(GetMaskFromPosition(i, j)) << "\n";

            // switch (positions[i * height + j]) {
            //     case 0: { myfile << "black\n"; break; }
            //     case 1: { myfile << "white\n"; break; }
            //     case 2: { myfile << "blue\n"; break; }
            //     case 3: { myfile << "yellow\n"; break; }
            //     case 4: { myfile << "red\n"; break; }
            //     case 5: { myfile << "green\n"; break; }

            //     default: {
            //         break;
            //     }
            // }
        }
    }

    myfile.close();
}

void MapGen::ClearFile(const char* file) {
    ofstream o;
    o.open("dummy.txt", ofstream::out | ofstream::trunc);
    o.close();
}