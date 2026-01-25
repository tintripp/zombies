#pragma once
typedef struct Game Game;

typedef struct StatePlayData {
    double px, py, pspeed;
} StatePlayData;

void state_play_enter(Game *game, StatePlayData *data);
void state_play_exit(Game *game, StatePlayData *data);

void state_play_do_event(Game *game, StatePlayData *data);
void state_play_do_update(Game *game, StatePlayData *data);
void state_play_do_draw(Game *game, StatePlayData *data);