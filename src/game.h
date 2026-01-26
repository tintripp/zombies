#pragma once
#include "raylib.h"
#include "state/state.h"
#include <stdbool.h>

#define GAME_VSCREEN_WIDTH  320
#define GAME_VSCREEN_HEIGHT 224
#define GAME_TITLE "STRAIGHT PROGRAM"

typedef struct Game {
    RenderTexture vscreen; // Virtual screen
    Font font;
    bool done;

    State *state;
} Game;

void game_init(Game *game);
void game_cleanup(Game *game);

void game_loop(Game *game);
void game_do_event(Game *game);
void game_do_update(Game *game);
void game_do_draw(Game *game);

void game_state_change(Game *game, State *next);
void game_request_exit(Game *game);