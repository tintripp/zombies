#include "raylib.h"

#include "../game.h"
#include "../objects/player.h"
#include "state_title.h"
#include "state_play.h"

#include <stdio.h>

void state_play_enter(Game *game, State *s) {
    StatePlay *data = (StatePlay *)s;
    
    data->plr = (Player){ 0 };
    player_init(&data->plr);

    // setup tiles
    tilemap_load(&data->tiles, "res/data/room/test.json");

    printf("Welcome to play time\n");
}
void state_play_exit(Game *game, State *s) {
    StatePlay *data = (StatePlay *)s;

    tilemap_free(&data->tiles);
    player_free(&data->plr);
}

void state_play_do_event(Game *game, State *s) {
    StatePlay *data = (StatePlay *)s;
    
    if (IsKeyPressed(KEY_BACKSLASH))
        game_request_exit(game);
    if (IsKeyPressed(KEY_ENTER))
        game_state_change(game, state_title());

    player_event(&data->plr, &data->tiles);

}
void state_play_do_update(Game *game, State *s) {
    StatePlay *data = (StatePlay *)s;

    player_update(&data->plr, &data->tiles);
}
void state_play_do_draw(Game *game, State *s) {
    StatePlay *data = (StatePlay *)s;

    ClearBackground(GRAY);

    tilemap_draw(&data->tiles);

    player_draw(&data->plr);

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