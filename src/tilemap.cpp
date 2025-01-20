#include "./h/tiles/tilemap.h"
#include "./h/tiles/tile.h"

#include <bitset>
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

/**
 * Creates a new `TileMap` object, which is used to store the contents of reading
 * a tile image and then display them in a matrix when rendered to the screen.
 * 
 * @param width The width of the screen in tiles. 
 * @param height The height of the screen in tiles.
 */
TileMap::TileMap(int width, int height) {
    this->width = width;
    this->height = height;

    map = {};
}

/**
 * Checks to see if the internal mapping contains a certain key.
 * 
 * @param elem The key to check for in the map.
 * @return If the key exists in the map.
 */
bool TileMap::ContainsKey(string elem) {
    auto f = map.find(elem);
    return f != map.end();
}

/**
 * Loads a series of tiles from an image (located at `image_file`) and matches it with
 * a list of names (located at `name_file`). These tiles are then stored in the internal
 * `map` of the tilemap. Tiles with the same name are combined.
 * 
 * Note that these locations are relative based on the folder specified by `resource_dir`.
 * 
 * @param image_file The image file location.
 * @param name_file The name file location.
 */
bool TileMap::LoadTiles(const char* image_file, const char* name_file, int width, int height) {
    ifstream names(name_file);
    string str;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            // Fetches the current line in the names file.
            std::getline(names, str);
            Tile* t;

            // If the name already exists, add the image to the pre-existing tile.
            if (ContainsKey(str)) {
                t = map.at(str);
                t->AddImage(image_file, i * 24, j * 24);
            } else {
                // If not, then make a new tile and add it to the tilemap mapping.

                t = new Tile(image_file, str, i * 24, j * 24);
                std::pair<string, Tile*> pair (str, t);
                map.insert(pair);
            }
        }
    }

    // Returns true if the process completes without any errors.
    return true;
}

/** 
 * Loads the tiles specified in `file` onto an image the size of the screen.
 * Tiles are originally loaded as `24 x 24` images, and then upscaled into 
 * `72 x 72` after they have been mapped onto the image.
 * 
 * This order was chosen since upscaling before mapping since raylib
 * uses a bilinear upscaling technique - which can lead to pixel overlap
 * (and nearest neighbor does not exist in raylib, for some reason).
 * 
 * @param file The list of tiles to read from.
 * @return The `Texture2D` of the finished tilemap.
 */
Texture2D TileMap::DisplayMap(const char* file) {
    ifstream tiles(file);
    string str;

    // The image chosen here is completely arbitrary.
    Image bg = LoadImage("forest_tilemap.png");
    ImageResize(&bg, 24 * width, 24 * height);

    // Reads the file and draws tiles COLUMN by COLUMN.
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            std::getline(tiles, str);

            if (!ContainsKey(str)) {
                int m = std::stoi(str);
                m |= 0b0000000101000101;
                // m ^= 0b0000000111101111;
                
                str = std::to_string(m);
            }
            if (!ContainsKey(str)) continue;

            Tile* t = map.at(str);
            t->TileDraw(bg, 24 * i, 24 * j);
        }
    }

    // Resize the image to fit the screen (upscale by 3x).
    ImageResize(&bg, 72 * width, 72 * height);

    Texture2D tex = LoadTextureFromImage(bg);

    UnloadImage(bg); 

    // Return the completed texture.
    return tex;
}

int TileMap::FetchWallmask(const char* file, int x, int y) {
    int mask = 0b0;

    cout << x << ", " << y << endl;

    Image img = LoadImage(file);
    ImageCrop(&img, {(float) x, (float) y, 24, 24});
    Color* colors = LoadImageColors(img);
    
    bool white_found = false;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int index = ((i * 8 + 4) * 24) + (j * 8 + 4);
            Color pixel = colors[index];
            
            mask <<= 1;
            if (pixel.r > 10 || pixel.g > 10 || pixel.b > 10) mask |= 1;
            if (pixel.r > 200 || pixel.g > 200 || pixel.b > 200) white_found = true;
        }
    }

    if (!white_found) mask <<= 3;

    cout << std::bitset<16>(mask) << endl;

    UnloadImageColors(colors);
    return mask;
}

void TileMap::LoadMaskedTiles(const char* image_file) {
    Image img = LoadImage(image_file);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < img.height / 25; j++) {
            int mask_x = i * 25;
            int mask_y = j * 25;

            int tile_x = i * 25 + 75;
            int tile_y = j * 25;

            int mask = FetchWallmask(image_file, mask_x, mask_y);
            string str = std::to_string(mask);
            Tile* tile;

            if (mask > 512) continue;

            if (ContainsKey(str)) {
                tile = map.at(str);
                tile->AddImage(image_file, tile_x, tile_y);
            } else {
                tile = new Tile(image_file, str, tile_x, tile_y);
                std::pair<string, Tile*> pair (str, tile);
                map.insert(pair);
            }
        }
    }
}