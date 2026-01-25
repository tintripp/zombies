#pragma once
typedef struct Game Game;

typedef struct StateTitleData {
    
} StateTitleData;

void state_title_enter(Game *game, StateTitleData *data);
void state_title_exit(Game *game, StateTitleData *data);

void state_title_do_event(Game *game, StateTitleData *data);
void state_title_do_update(Game *game, StateTitleData *data);
void state_title_do_draw(Game *game, StateTitleData *data);