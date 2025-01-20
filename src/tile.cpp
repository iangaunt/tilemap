#include "./h/tiles/tile.h"

#include <string>
#include <vector>

#include <raylib.h>
#include <stdlib.h>
#include <time.h>

using std::string;
using std::vector;

/**
 * Creates a new Tile object. Starts off as empty with a
 * preloaded empty `textures` vector to store images.
 */
Tile::Tile() {
    textures = new vector<Image>();
}

/**
 * Creates a new Tile from the top `24 x 24` pixels located at `file`.
 * The tile is then internally named `name`. 
 * 
 * @param file The file to crop from. Takes the top left tile.
 * @param name The name of the tile.
 */
Tile::Tile(const char* file, string name) {
    textures = new vector<Image>();
    this->name = name;
    
    Image image = LoadImage(file);
    ImageCrop(&image, {0, 0, 24, 24});
    textures->push_back(image);
}

/**
 * Creates a new Tile from the `24 x 24` pixels, starting at `(x, y)` 
 * located at `file`. The tile is then internally named `name`. 
 * 
 * @param file The file to crop from. Takes the top left tile.
 * @param name The name of the tile.
 * @param x The x of the top-left corner of the tile.
 * @param y The y of the top-left corner of the tile.
 */
Tile::Tile(const char* file, string nameh, int x, int y) {
    textures = new vector<Image>();
    name = nameh;

    Image image = LoadImage(file);
    ImageCrop(&image, {(float) x, (float) y, 24, 24});
    textures->push_back(image);
}

/**
 * Draws the tile at `(x, y)` on the given image. The image will be
 * randomly selected from the list of available images.
 * 
 * @param img The image to draw on.
 * @param x The x coordinate of the top-left corner to draw from.
 * @param y The y coordinate of the top-left corner to draw from.
 */
void Tile::TileDraw(Image img, int x, int y) {
    int r = rand() % textures->size();
    if (name == "16") r = 0;

    ImageDraw(
        &img, 
        textures->at(r), 
        {0, 0, 24, 24}, 
        {(float) x, (float) y, 24, 24}, 
        WHITE
    );
}

/**
 * Draws the tile at `(x, y)` on the given image. The image drawn
 * is located at `index` in the internal image array.
 * 
 * @param img The image to draw on.
 * @param x The x coordinate of the top-left corner to draw from.
 * @param y The y coordinate of the top-left corner to draw from.
 * @param index The index of the image in the tile array.
 */
void Tile::TileDraw(Image img, int x, int y, int index) {
    ImageDraw(
        &img, 
        textures->at(index), 
        {0, 0, 24, 24}, 
        {(float) x, (float) y, 24, 24}, 
        WHITE
    );
}

/**
 * Adds an image to the internal image array by cutting a `24 x 24` square
 * from `file`, starting at `(x, y)`.
 * 
 * @param file The file to pull from.
 * @param x The x coordinate of the top-left corner to cut from.
 * @param y The y coordinate of the top-left corner to cut from.
 */
void Tile::AddImage(const char* file, int x, int y) {
    Image image = LoadImage(file);
    ImageCrop(&image, {(float) x, (float) y, 24, 24});
    textures->push_back(image);
}

/** Unloads the images inside the internal tile buffer. */
Tile::~Tile() {
    for (int i = 0; i < (int) (textures->size()); i++) {
        UnloadImage(textures->at(i));
    }
}