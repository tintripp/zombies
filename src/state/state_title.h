#pragma once
#include "state.h"

typedef struct StateTitle {
    State base;
    double time_elapsed;
} StateTitle;

void state_title_enter(Game *game, State *state);
void state_title_exit(Game *game, State *state);

void state_title_do_update(Game *game, State *state);
void state_title_do_draw(Game *game, State *state);

State *state_title();