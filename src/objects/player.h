#pragma once
#include "raylib.h"
#include "tilemap.h"

typedef enum PlayerDirection {
    PLRDIR_RIGHT = 1,
    PLRDIR_LEFT = -1
} PlayerDirection;

typedef struct Player Player;

struct Player{
    Texture sprite;
    Rectangle hitbox;
    Vector2 velocity;
    Vector2 remainder;

    PlayerDirection dir;
    float anim_frame;
    int frame_offx, frame_offy, frame_w, frame_h;

    float speed;
};

void player_init(Player *player);
void player_free(Player *player);

void player_update(Player *player, TileMap *tiles);
void player_draw(Player *player);

void player_move(Player *player, TileMap *tiles, Vector2 dv);
bool player_is_on_ground(Player *player, TileMap *tilemap); 