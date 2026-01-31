#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "tilemap.h"
#include <stdio.h>
#include <stdlib.h>

void player_init(Player *player){
    player->sprite = LoadTexture("res/images/onionboy.png");
    player->dir = PLRDIR_RIGHT;

    player->anim_frame = 0;
    player->frame_offx = 4;
    player->frame_offy = 15;
    player->frame_w = 16;
    player->frame_h = 23;

    player->velocity = (Vector2){ 0, 0 };
    player->hitbox = (Rectangle){ 80, 30, 8, 8 }; 
    player->speed = 6;
}
void player_free(Player *player){
    UnloadTexture(player->sprite);
}

void player_event(Player *player, TileMap *tilemap){
    if (IsKeyPressed(KEY_W) && player_is_on_ground(player, tilemap))
        player->velocity.y = -160;
}
void player_update(Player *player, TileMap *tilemap){
    player->velocity.x += (
        IsKeyDown(KEY_D) - IsKeyDown(KEY_A)
    ) * player->speed;
    player->velocity.x *= 0.95;

    player->anim_frame += abs((int)player->velocity.x) * GetFrameTime() / 8;
    if (player->velocity.x < 0) player->dir = PLRDIR_LEFT;
    if (player->velocity.x > 0) player->dir = PLRDIR_RIGHT;

    //gravity
    player->velocity.y += 360 * GetFrameTime();
    
    player_move(player, tilemap, Vector2Scale(player->velocity, GetFrameTime()));
}
void player_draw(Player *player){
    if (!round(player->velocity.x)){
        player->anim_frame = 0;
    }
    //soon 2 will be anim length -- make json parsing work
    int frame = ((int)player->anim_frame % 2); 

    DrawTextureRec(
        player->sprite, 
        (Rectangle){
            player->frame_w * frame, 0,
            player->frame_w * player->dir, player->frame_h
        }, 
        (Vector2){ 
            player->hitbox.x - player->frame_offx, 
            player->hitbox.y - player->frame_offy 
        }, 
        WHITE
    );

    //debug
    int left = player->hitbox.x / TILE_SIZE;
    int right = (player->hitbox.x + player->hitbox.width) / TILE_SIZE;
    int top = player->hitbox.y / TILE_SIZE;
    int bottom = (player->hitbox.y + player->hitbox.height) / TILE_SIZE;

    //DrawRectangleLines(left * TILE_SIZE, top * TILE_SIZE, (right - left + 1) * TILE_SIZE, (bottom - top + 1) * TILE_SIZE, GREEN);
    
    DrawRectangleRec(player->hitbox, PINK);
}

bool player_is_colliding(Player *player, TileMap *tilemap){
    bool collided = false;

    int left = player->hitbox.x / TILE_SIZE;
    int right = (player->hitbox.x + player->hitbox.width - 1) / TILE_SIZE;
    int top = player->hitbox.y / TILE_SIZE;
    int bottom = (player->hitbox.y + player->hitbox.height - 1) / TILE_SIZE;

    for (int r = top; r <= bottom; r++){
        for (int c = left; c <= right; c++){
            TileType tile = tilemap_get_at(tilemap, r, c);

            if (tile == TILE_BRICK) {
                collided = true;
                break;
            }

        }
        if (collided) break;
    }
    return collided;
}

bool player_is_on_ground(Player *player, TileMap *tilemap){
    ++player->hitbox.y;
    bool on_ground = player_is_colliding(player, tilemap);
    --player->hitbox.y;
    return on_ground;
}

void player_move_axis(
    Player *player, 
    TileMap *tilemap, 
    float *remainder, 
    float *hitbox_pos, 
    float *velocity, 
    float dv
) {
    float total = dv + *remainder;
    int amt = (int)total;
    *remainder = total - amt;

    int sign = (amt > 0) - (amt < 0);

    while (amt != 0){
        *hitbox_pos += sign;

        // this loops through every tile.. 
        // make a function to find only tilemap the hitbox is in.

        if (player_is_colliding(player, tilemap)){
            *hitbox_pos -= sign;
            *velocity = 0;
            break;
        }

        amt -= sign;
    }

}

void player_move(Player *player, TileMap *tilemap, Vector2 dv) {
    player_move_axis(player, tilemap, 
        &player->remainder.x, 
        &player->hitbox.x, 
        &player->velocity.x, 
        dv.x
    );
    player_move_axis(player, tilemap, 
        &player->remainder.y, 
        &player->hitbox.y, 
        &player->velocity.y, 
        dv.y
    );
}