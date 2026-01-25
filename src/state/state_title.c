#include "raylib.h"

#include "../game.h"
#include "state_title.h"
#include "state_play.h"

#include <stdio.h>
#include <math.h>

void state_title_enter(Game *game, State *state){
    StateTitle *data = (StateTitle *)state;
    data->time_elapsed = 0;

    printf("Welcome to title time\n");
}
void state_title_exit(Game *game, State *state){
    
}

void state_title_do_event(Game *game, State *state){
    if (IsKeyPressed(KEY_SPACE))
        printf("JARED ROCKS\n");
    if (IsKeyPressed(KEY_ENTER))
        game_state_change(game, state_play());
}
void state_title_do_update(Game *game, State *state){
    StateTitle *data = (StateTitle *)state;
    data->time_elapsed += GetFrameTime();
}
void state_title_do_draw(Game *game, State *state){
    StateTitle *data = (StateTitle *)state;

    ClearBackground(GRAY);
    
    {
        double xoff = sin(data->time_elapsed + 1) / 2 * 8;
        double yoff = sin(data->time_elapsed * 2) * 50;

        char *msg = "I love u jared";
        int fontsize = 16;

        Vector2 size = MeasureTextEx(game->font, msg, fontsize, xoff);

        DrawTextEx(
            game->font, 
            msg, 
            (Vector2){
                (GAME_VSCREEN_WIDTH / 2) - (size.x / 2), 
                (GAME_VSCREEN_HEIGHT / 2) - (size.y / 2) + yoff
            }, 
            fontsize, 
            xoff, 
            WHITE
        );
    }
    
}

State *state_title() {
    static StateTitle state = {
        .base = {
            .enter = state_title_enter,
            .exit = state_title_exit,
            .do_event = state_title_do_event,
            .do_update = state_title_do_update,
            .do_draw = state_title_do_draw
        }
    };
    return &state.base;
}