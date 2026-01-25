#include "state_play.h"
#include "raylib.h"
#include "../game.h"
#include <stdio.h>

void state_play_enter(Game *game, StatePlayData *data) {
    data->px = 0;
    data->py = 0;
    data->pspeed = 120;

    printf("Welcome to play time\n");
}
void state_play_exit(Game *game, StatePlayData *data) {

}

void state_play_do_event(Game *game, StatePlayData *data) {
    
    if (IsKeyPressed(KEY_BACKSLASH))
        game_exit(game);
    if (IsKeyPressed(KEY_ENTER))
        game_state_change(game, STATE_TITLE);

}
void state_play_do_update(Game *game, StatePlayData *data) {
    data->px += (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * GetFrameTime() * data->pspeed;
    data->py += (IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) * GetFrameTime() * data->pspeed;
}
void state_play_do_draw(Game *game, StatePlayData *data) {
    ClearBackground(BLACK);
    
    DrawRectangle(data->px, data->py, 64, 64, PINK);

    DrawTextEx(game->font, "Welcome to play time!\nBackslash will exit.!", (Vector2){0,70}, 8, 0, WHITE);
}