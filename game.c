#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "raylib.h"

int main(void) {
    int windowWidth = 640;
    int windowHeight = 480;
    char *windowTitle = "Blocks";

    InitWindow(windowWidth, windowHeight, windowTitle);

    SetTargetFPS(120);

    bool gameOver = false;
    bool exitWindow = false;
    bool exitWindowRequested = false;
    while (!exitWindow) {
        {
            if (WindowShouldClose()) exitWindowRequested = true;
            if (gameOver && IsKeyPressed(KEY_ESCAPE)) {
                exitWindowRequested = true;
            }
            if (exitWindowRequested) {
                exitWindow = true;
            }
        }

        if (!gameOver) {
        }

        BeginDrawing();
        {
            ClearBackground(GetColor(0x000000FF));
            DrawFPS(50, 50);


            if (gameOver) {
                int textWidth = MeasureText("GAME OVER", 20);
                DrawText("GAME OVER", windowWidth-textWidth-textWidth/2, 5, 20, WHITE);
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
