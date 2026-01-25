#pragma once
#include "raylib.h"
#include "state/states.h"
#include <stdbool.h>

#define GAME_VSCREEN_WIDTH  240
#define GAME_VSCREEN_HEIGHT 180
#define GAME_TITLE "STRAIGHT PROGRAM"

typedef struct Game {
    RenderTexture vscreen; // Virtual screen
    Font font;
    bool done;

    State state;
    State state_next;
    bool state_done;

    StateTitleData state_title_data;
    StatePlayData state_play_data;
} Game;

void game_init(Game *game);
void game_exit(Game *game);

void game_loop(Game *game);
void game_do_event(Game *game);
void game_do_update(Game *game);
void game_do_draw(Game *game);

void game_state_change(Game *game, State next);