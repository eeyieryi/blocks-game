#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>

#include "raylib.h"

#define NUM_BLOCKS 7
#define NUM_TILES 8
int blocks[NUM_BLOCKS][NUM_TILES] = {
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

#define INITIALIZE_BOARD_WITH 0
void ResetBoard() {
    for (int i = 0; i < NUM_LINES; i++)
        for (int j = 0; j < NUM_COLUMNS; j++)
            board[i][j] = INITIALIZE_BOARD_WITH;
}

int main(void) {
    int windowWidth = 640;
    int windowHeight = 480;
    char *windowTitle = "Blocks";

    ResetBoard();

    InitWindow(windowWidth, windowHeight, windowTitle);
    SetTargetFPS(120);


    int *currentBlock = blocks[0];
    int currentX = 1;
    int currentY = 1;


    double seconds = 0;

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
            double dt = GetFrameTime();
            seconds += dt;
            if (seconds >= (1)) {
                seconds = 0;
                currentY += 1;
            }
        }

        if (IsKeyPressedRepeat(KEY_DOWN) || IsKeyPressed(KEY_DOWN)) {
            currentY += 1;
        }
        if (IsKeyPressedRepeat(KEY_LEFT) || IsKeyPressed(KEY_LEFT)) {
            currentX -= 1;
        }
        if (IsKeyPressedRepeat(KEY_RIGHT) || IsKeyPressed(KEY_RIGHT)) {
            currentX += 1;
        }

        BeginDrawing();
        {
            ClearBackground(GetColor(0x000000FF));

            {
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

                startOffsetX = tileWidth * 10 + 1;
                offsetX = startOffsetX;
                offsetY = tileWidth*1.5+1;
                for (int i = 0; i < NUM_LINES; i++) {
                    for (int j = 0; j < NUM_COLUMNS; j++) {
                        if (board[i][j] == 1) DrawRectangle(offsetX, offsetY, tileWidth, tileWidth, WHITE);
                        offsetX += tileWidth + 1;
                    }
                    offsetX = startOffsetX;
                    offsetY += tileWidth + 1;
                }

                startOffsetX = (tileWidth*10+1)+(currentX*(tileWidth+1));
                startOffsetY = (tileWidth*1.5+1)+(currentY*(tileWidth+1));
                offsetX = startOffsetX;
                offsetY = startOffsetY;
                for (int i = 0; i < NUM_TILES; i++) {
                    if (currentBlock[i] == 1) {
                        DrawRectangle(offsetX, offsetY, tileWidth, tileWidth, RED);
                    }
                    offsetX += tileWidth+1;
                    if (i == 3) {
                        offsetY += tileWidth+1;
                        offsetX = startOffsetX;
                    }
                }
            }

            {
                DrawFPS(50, 50);

                char c[100];
                sprintf(c, "%0.4f", seconds);
                DrawText(c, 50, 20, 20, WHITE);

                if (gameOver) {
                    int textWidth = MeasureText("GAME OVER", 20);
                    DrawText("GAME OVER", windowWidth-textWidth-textWidth/2, 5, 20, WHITE);
                }
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
