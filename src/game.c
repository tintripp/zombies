#include "game.h"
#include "raylib.h"
#include <stdio.h>

void game_init(Game *game){
    game->done = false;

    game->state = -1;
    game->state_next = STATE_TITLE;
    game->state_done = true;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(GAME_VSCREEN_WIDTH * 2, GAME_VSCREEN_HEIGHT * 2, GAME_TITLE);
    SetWindowMinSize(GAME_VSCREEN_WIDTH, GAME_VSCREEN_HEIGHT);
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    game->vscreen = LoadRenderTexture(GAME_VSCREEN_WIDTH, GAME_VSCREEN_HEIGHT);
    game->font = LoadFont("res/PixelOperator8-Bold.ttf");

}
void game_exit(Game *game){
    game->done = true;
}

void game_loop(Game *game){
    while (!WindowShouldClose() && !game->done){
        if (game->state_done && game->state_next >= 0){
            game->state_done = false;

            // call correct state->exit
            switch(game->state) {
                case STATE_TITLE:
                    state_title_exit(game, &game->state_title_data); break;
                case STATE_PLAY:
                    state_play_exit(game, &game->state_play_data); break;
            }
            game->state = game->state_next;
            switch(game->state) {
                case STATE_TITLE:
                    state_title_enter(game, &game->state_title_data); break;
                case STATE_PLAY:
                    state_play_enter(game, &game->state_play_data); break;
            }
            
            // call correct state->enter
        }

        game_do_event(game);
        game_do_update(game);
        game_do_draw(game);
    }

    UnloadRenderTexture(game->vscreen);
    CloseWindow();
}

void game_do_event(Game *game){
    switch(game->state) {
        case STATE_TITLE:
            state_title_do_event(game, &game->state_title_data); break;
        case STATE_PLAY:
            state_play_do_event(game, &game->state_play_data); break;
    }
}

void game_do_update(Game *game){
    switch(game->state) {
        case STATE_TITLE:
            state_title_do_update(game, &game->state_title_data); break;
        case STATE_PLAY:
            state_play_do_update(game, &game->state_play_data); break;
    }
}

void game_do_draw(Game *game){
    BeginTextureMode(game->vscreen);
    switch(game->state) {
        case STATE_TITLE:
            state_title_do_draw(game, &game->state_title_data); break;
        case STATE_PLAY:
            state_play_do_draw(game, &game->state_play_data); break;
    }
    EndTextureMode();

    BeginDrawing();
        ClearBackground(BLACK);

        int xmult = GetScreenWidth() / GAME_VSCREEN_WIDTH;
        int ymult = GetScreenHeight() / GAME_VSCREEN_HEIGHT;
        if (xmult < ymult) ymult = xmult;
        if (ymult < xmult) xmult = ymult;

        

        DrawTexturePro(
            game->vscreen.texture, 

            (Rectangle){0, 0, 
                (float)GAME_VSCREEN_WIDTH, -(float)GAME_VSCREEN_HEIGHT},
            
            (Rectangle){ 
                (GetScreenWidth() - (GAME_VSCREEN_WIDTH * xmult)) / 2, 
                (GetScreenHeight() - (GAME_VSCREEN_HEIGHT * ymult)) / 2, 
                (float)GAME_VSCREEN_WIDTH * xmult, 
                (float)GAME_VSCREEN_HEIGHT * ymult, 
            },

            (Vector2){ 0, 0 }, 0, WHITE
            
        );
    EndDrawing();
}

void game_state_change(Game *game, State next){
    game->state_done = true;
    game->state_next = next;
}