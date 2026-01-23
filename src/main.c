#include "raylib.h"
#include <stdio.h>
#include <math.h>

int main(void) {
    InitWindow(800, 450, "STRAIGHT PROGRAM");

    Font font = LoadFont("res/PixelOperator8-Bold.ttf");

    SetTargetFPS(60);


    int px = 0, py = 0;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_A))
            printf("JARED ROCKS\n");

        BeginDrawing();
        ClearBackground(GRAY);
        if (IsKeyDown(KEY_A)){
            double result = sin(GetTime());
            
            DrawTextEx(font, "I love u jared", (Vector2){0, (result+1)*90}, 40, ((result + 1) / 2) * 32, WHITE);
        }

        px += (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * 2;
        py += (IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) * 2;
        
        DrawFPS(px,py);


        EndDrawing();
    }
    CloseWindow();
    return 0;
}
