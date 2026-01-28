#pragma once
#include "../cJSON.h"

// Dude... im thinking 8 is a better size. 16 for testing tho!
#define TILE_SIZE 16 

typedef enum TileType {
    TILE_AIR = 0,
    TILE_BRICK,
    TILE_SPIKE
} TileType;

typedef struct TileMap {
    // a flattened 2d array containing map tiles.
    TileType *tiles;
    int w, h;
} TileMap;

// futureproofing, it will return 0 on success
int tilemap_loadJSON(TileMap *tilemap, const char *filepath); 

void tilemap_free(TileMap *tilemap);
void tilemap_draw(TileMap *tilemap);

TileMap tilemap_tiles_behind(TileMap *tilemap, Rectangle rect);
TileType tilemap_get_at(TileMap *tilemap, int row, int col);