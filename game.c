#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>

#include "raylib.h"

#define NUM_BLOCKS 7
#define NUM_TILES 8
const int blocks[NUM_BLOCKS][NUM_TILES] = {
    {
        1, 1, 1, 0,
        0, 1, 0, 0,
    },
    {
        0, 1, 1, 0,
        1, 1, 0, 0,
    },
    {
        1, 1, 0, 0,
        0, 1, 1, 0,
    },
    {
        1, 1, 1, 1,
        0, 0, 0, 0,
    },
    {
        1, 1, 1, 0,
        1, 0, 0, 0,
    },
    {
        1, 1, 1, 0,
        0, 0, 1, 0,
    },
    {
        1, 1, 0, 0,
        1, 1, 0, 0,
    },
};

#define NUM_LINES 20
#define NUM_COLUMNS 10
int board[NUM_LINES][NUM_COLUMNS];

void ResetBoard() {
    for (int i = 0; i < NUM_LINES; i++)
        for (int j = 0; j < NUM_COLUMNS; j++)
            board[i][j] = 0;
}

int main(void) {
    int windowWidth = 640;
    int windowHeight = 480;
    char *windowTitle = "Blocks";

    ResetBoard();

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


            int tileWidth = 20;
            int startOffsetX = windowWidth - tileWidth * 5;
            int startOffsetY = 20;
            int offsetX = startOffsetX;
            int offsetY = startOffsetY;
            for (int i = 0; i < NUM_BLOCKS; i++) {
                for (int j = 0; j < NUM_TILES; j++) {
                    if (blocks[i][j] == 1) {
                        DrawRectangle(offsetX, offsetY, tileWidth, tileWidth, RED);
                    } else {
                        DrawRectangle(offsetX, offsetY, tileWidth, tileWidth, BLUE);
                    }
                    offsetX += tileWidth+1;
                    if (j == 3) {
                        offsetX = startOffsetX;
                        offsetY += tileWidth+1;
                    }
                }
                offsetX = startOffsetX;
                offsetY += tileWidth*2+1;
            }

            startOffsetX = tileWidth * 9;
            offsetX = startOffsetX;
            offsetY = tileWidth / 2;
            for (int i = 0; i <= NUM_LINES+1; i++) {
                for (int j = 0; j <= NUM_COLUMNS+1; j++) {
                    if (i == 0 || j == 0 || i == NUM_LINES+1 || j == NUM_COLUMNS+1) {
                        DrawRectangle(offsetX, offsetY, tileWidth, tileWidth, DARKBLUE);
                    }
                    offsetX += tileWidth + 1;
                }
                offsetX = startOffsetX;
                offsetY += tileWidth + 1;
            }

            startOffsetX = tileWidth * 10;
            offsetX = startOffsetX;
            offsetY = tileWidth*1.5;
            for (int i = 0; i < NUM_LINES; i++) {
                for (int j = 0; j < NUM_COLUMNS; j++) {
                    if (board[i][j] == 1) DrawRectangle(offsetX, offsetY, tileWidth, tileWidth, WHITE);
                    offsetX += tileWidth + 1;
                }
                offsetX = startOffsetX;
                offsetY += tileWidth + 1;
            }

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
