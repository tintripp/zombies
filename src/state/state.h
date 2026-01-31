#pragma once

typedef struct Game Game;
typedef struct State State;

struct State {
    void (*enter)       (Game*, State*);
    void (*exit)        (Game*, State*);

    void (*do_update)   (Game*, State*);
    void (*do_draw)     (Game*, State*);
};