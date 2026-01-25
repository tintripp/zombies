#include "state_title.h"
#include "raylib.h"
#include "../game.h"
#include <stdio.h>
#include <math.h>

void state_title_enter(Game *game, StateTitleData *data){
    printf("Welcome to title time\n");
}
void state_title_exit(Game *game, StateTitleData *data){
    
}

void state_title_do_event(Game *game, StateTitleData *data){
    if (IsKeyPressed(KEY_SPACE))
        printf("JARED ROCKS\n");
    if (IsKeyPressed(KEY_ENTER))
        game_state_change(game, STATE_PLAY);
}
void state_title_do_update(Game *game, StateTitleData *data){

}
void state_title_do_draw(Game *game, StateTitleData *data){
    ClearBackground(GRAY);
    
    {
        double xoff = ((sin(GetTime()) + 1) / 2) * 8;
        double yoff = (sin(GetTime()*2)) * 50;

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