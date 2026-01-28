#include "raylib.h"
#include "../cJSON.h"
#include "tilemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TileType tilemap_deduce_type(char *type){
    if (strcmp(type, "brick") == 0) return TILE_BRICK;
    if (strcmp(type, "spike") == 0) return TILE_SPIKE;
    return TILE_AIR;    
}


TileMap tilemap_tiles_behind(TileMap *tilemap, Rectangle rect){

}

TileType tilemap_get_at(TileMap *tilemap, int row, int col){
    if (row < 0 || row >= tilemap->h || col < 0 || col >= tilemap->w)
        return TILE_AIR;
    return tilemap->tiles[row * tilemap->w + col];
}

int tilemap_loadJSON(TileMap *tilemap, const char *filepath){
    char *json_str = LoadFileText(filepath);
    if (!json_str){
        printf("Could not open the file!!");
        return 1;
    }

    cJSON *json = cJSON_Parse(json_str);
    if (!json){
        printf("Could not parse the file!! %s", cJSON_GetErrorPtr());
        free(json_str);
        return 1;
    }

    int width = cJSON_GetObjectItem(json, "width")->valueint;
    int height = cJSON_GetObjectItem(json, "height")->valueint;

    TileType *tiles = calloc(width * height, sizeof(TileType));

    cJSON *json_arr = cJSON_GetObjectItem(json, "tiles");

    for (int i = 0; i < cJSON_GetArraySize(json_arr); i++){
        cJSON *tile = cJSON_GetArrayItem(json_arr, i);
        int r = cJSON_GetObjectItem(tile, "y")->valueint;
        int c = cJSON_GetObjectItem(tile, "x")->valueint;

        cJSON *type = cJSON_GetObjectItem(tile, "t");
        if (!type || !type->valuestring) return 1;
        char *type_str = type->valuestring;
        
        //printf("%s\n", type_str);

        tiles[r * width + c] = tilemap_deduce_type(type_str);
    }
    
    cJSON_Delete(json);
    free(json_str);

    // finally, assign.
    tilemap->w = width;
    tilemap->h = height;
    tilemap->tiles = tiles;

    return 0;
}
void tilemap_free(TileMap *tilemap){
    free(tilemap->tiles);
}

void tilemap_draw(TileMap *tilemap){
    for (int r = 0; r < tilemap->h; r++){
        for (int c = 0; c < tilemap->w; c++){
            TileType tile = tilemap_get_at(tilemap, r, c);

            if (tile == TILE_BRICK)
                DrawRectangle(
                    c * TILE_SIZE, r * TILE_SIZE, 
                    TILE_SIZE, TILE_SIZE, 
                    RED
                );
            if (tile == TILE_SPIKE)
                DrawRectangle(
                    c * TILE_SIZE, r * TILE_SIZE, 
                    TILE_SIZE, TILE_SIZE, 
                    BLUE
                );
        }
    }
}