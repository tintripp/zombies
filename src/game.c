#include "raylib.h"

#include "game.h"
#include "state/state_title.h"

#include <stdio.h>

void game_init(Game *game){
    game->done = false;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(GAME_VSCREEN_WIDTH * 2, GAME_VSCREEN_HEIGHT * 2, GAME_TITLE);
    SetWindowMinSize(GAME_VSCREEN_WIDTH, GAME_VSCREEN_HEIGHT);
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    game->vscreen = LoadRenderTexture(GAME_VSCREEN_WIDTH, GAME_VSCREEN_HEIGHT);
    game->font = LoadFont("res/PixelOperator8-Bold.ttf");

    game_state_change(game, state_title());

}
void game_cleanup(Game *game){
    UnloadRenderTexture(game->vscreen);
    CloseWindow();
}

void game_loop(Game *game){
    game_init(game);

    while (!WindowShouldClose() && !game->done){
        game_do_event(game);
        game_do_update(game);
        game_do_draw(game);
    }

    game_cleanup(game);
}

void game_do_event(Game *game){
    if (
        IsKeyPressed(KEY_F11) ||

        // either alt + enter
        ((IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)) && 
        IsKeyPressed(KEY_ENTER))
    ){
        ToggleFullscreen();
        return; // state shouldn't process a fullscreen req
    }

    game->state->do_event(game, game->state);
}

void game_do_update(Game *game){
    game->state->do_update(game, game->state);
}

void game_do_draw(Game *game){
    BeginTextureMode(game->vscreen);
        game->state->do_draw(game, game->state);

        // FPS (test)
        DrawTextEx(
            game->font, 
            TextFormat("%i", GetFPS()), 
            (Vector2){0, 0}, 
            8, 0, BLUE
        );
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

void game_state_change(Game *game, State *next){
    if (game->state)
        game->state->exit(game, game->state);

    game->state = next;

    game->state->enter(game, game->state);
}

void game_request_exit(Game *game){
    game->done = true;
}