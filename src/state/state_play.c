#include "raylib.h"

#include "../game.h"
#include "state_title.h"
#include "state_play.h"

#include <stdio.h>

void state_play_enter(Game *game, State *s) {
    StatePlay *data = (StatePlay *)s;

    data->px = 0;
    data->py = 0;
    data->pspeed = 120;

    printf("Welcome to play time\n");
}
void state_play_exit(Game *game, State *s) {

}

void state_play_do_event(Game *game, State *s) {
    
    if (IsKeyPressed(KEY_BACKSLASH))
        game_request_exit(game);
    if (IsKeyPressed(KEY_ENTER))
        game_state_change(game, state_title());

}
void state_play_do_update(Game *game, State *s) {
    StatePlay *data = (StatePlay *)s;

    data->px += (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * GetFrameTime() * data->pspeed;
    data->py += (IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) * GetFrameTime() * data->pspeed;
}
void state_play_do_draw(Game *game, State *s) {
    StatePlay *data = (StatePlay *)s;

    ClearBackground(BLACK);
    DrawRectangle(data->px, data->py, 64, 64, PINK);
    DrawTextEx(game->font, "Welcome to play time!\nBackslash will exit.!", (Vector2){0,70}, 8, 0, WHITE);
}

State *state_play() {
    static StatePlay state = {
        .base = {
            .enter = state_play_enter,
            .exit = state_play_exit,
            .do_event = state_play_do_event,
            .do_update = state_play_do_update,
            .do_draw = state_play_do_draw
        },
    };
    return &state.base;
}