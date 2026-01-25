#pragma once
#include "state.h"

typedef struct StatePlay {
    State base;
    double px, py, pspeed;
} StatePlay;

void state_play_enter(Game *game, State *state);
void state_play_exit(Game *game, State *state);

void state_play_do_event(Game *game, State *state);
void state_play_do_update(Game *game, State *state);
void state_play_do_draw(Game *game, State *state);

State *state_play();