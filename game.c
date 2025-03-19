#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "raylib.h"

#define NUM_LINES 20
#define NUM_COLUMNS 10
int board[NUM_LINES][NUM_COLUMNS];
#define INITIALIZE_BOARD_WITH 0
void ResetBoard() {
    for (int i = 0; i < NUM_LINES; i++)
        for (int j = 0; j < NUM_COLUMNS; j++)
            board[i][j] = INITIALIZE_BOARD_WITH;
}

#define MAX_ROTATIONS 4
#define MAX_CELLS 16
typedef struct Block {
    int rowLength;
    int colLength;
    int cellLength; // row*col
    int rotationLength;
    int rotations[MAX_ROTATIONS][MAX_CELLS];
} Block;

const Block blockA = {
    .rotationLength = 4,
    .rowLength = 3,
    .colLength = 3,
    .cellLength = 9,
    .rotations = {
        {
            1, 1, 1,
            0, 1, 0,
            0, 0, 0,
        },
        {
            1, 0, 0,
            1, 1, 0,
            1, 0, 0,
        },
        {
            0, 0, 0,
            0, 1, 0,
            1, 1, 1,
        },
        {
            0, 1, 0,
            1, 1, 0,
            0, 1, 0,
        },
    },
};

const Block blockB = {
    .rowLength = 3,
    .colLength = 3,
    .cellLength = 9,
    .rotationLength = 4,
    .rotations = {
        {
            0, 0, 0,
            1, 1, 1,
            0, 0, 1,
        },
        {
            0, 1, 1,
            0, 1, 0,
            0, 1, 0,
        },
        {
            1, 0, 0,
            1, 1, 1,
            0, 0, 0,
        },
        {
            0, 1, 0,
            0, 1, 0,
            1, 1, 0,
        },
    },
};

const Block blockC = {
    .rowLength = 3,
    .colLength = 3,
    .cellLength = 9,
    .rotationLength = 4,
    .rotations = {
        {
            0, 0, 0,
            1, 1, 0,
            0, 1, 1,
        },
        {
            0, 0, 1,
            0, 1, 1,
            0, 1, 0,
        },
        {
            0, 0, 0,
            1, 1, 0,
            0, 1, 1,
        },
        {
            0, 0, 1,
            0, 1, 1,
            0, 1, 0,
        },
    },
};

const Block blockD = {
    .rotationLength = 1,
    .rowLength = 2,
    .colLength = 2,
    .cellLength = 4,
    .rotations = {
        {
            1, 1,
            1, 1,
        },
    },
};

const Block blockE = {
    .rotationLength = 4,
    .rowLength = 3,
    .colLength = 3,
    .cellLength = 9,
    .rotations = {
        {
            0, 0, 0,
            0, 1, 1,
            1, 1, 0,
        },
        {
            0, 1, 0,
            0, 1, 1,
            0, 0, 1,
        },
        {
            0, 0, 0,
            0, 1, 1,
            1, 1, 0,
        },
        {
            0, 1, 0,
            0, 1, 1,
            0, 0, 1,
        },
    },
};

const Block blockF = {
    .rowLength = 3,
    .colLength = 3,
    .cellLength = 9,
    .rotationLength = 4,
    .rotations = {
        {
            0, 0, 0,
            1, 1, 1,
            1, 0, 0,
        },
        {
            0, 1, 0,
            0, 1, 0,
            0, 1, 1,
        },
        {
            0, 0, 1,
            1, 1, 1,
            0, 0, 0,
        },
        {
            1, 1, 0,
            0, 1, 0,
            0, 1, 0,
        },
    },
};

const Block blockG = {
    .rotationLength = 2,
    .rowLength = 4,
    .colLength = 4,
    .cellLength = 16,
    .rotations = {
        {
            0, 0, 0, 0,
            0, 0, 0, 0,
            1, 1, 1, 1,
            0, 0, 0, 0,
        },
        {
            0, 0, 1, 0,
            0, 0, 1, 0,
            0, 0, 1, 0,
            0, 0, 1, 0,
        },
     },
};

#define NUM_BLOCKS 7
Block blocks[NUM_BLOCKS] = { blockA, blockB, blockC, blockD, blockE, blockF, blockG };

int main(void) {
    int windowWidth = 640;
    int windowHeight = 480;
    char *windowTitle = "Blocks";

    ResetBoard();

    InitWindow(windowWidth, windowHeight, windowTitle);
    SetTargetFPS(120);

    int currentBlockNumber = 0;
    Block *currentBlock = &blocks[currentBlockNumber];
    int currentRotation = 0;
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

        if (IsKeyPressed(KEY_UP)) {
            currentRotation = (currentRotation + 1) % (currentBlock)->rotationLength;
        }

        if (IsKeyPressed(KEY_SPACE)) {
            currentBlockNumber = (currentBlockNumber + 1) % NUM_BLOCKS;
            currentBlock = &blocks[currentBlockNumber];
        }

        BeginDrawing();
        {
            ClearBackground(GetColor(0x000000FF));

            {
                int tileWidth = 20;
                int originalOffsetX = windowWidth - tileWidth * 10;
                int originalOffsetY = 20;
                int startOffsetX = originalOffsetX;
                int startOffsetY = originalOffsetY;
                int offsetX = startOffsetX;
                int offsetY = startOffsetY;
                Block *block;
                for (int i = 0; i < NUM_BLOCKS; i++) {
                    block = &blocks[i];
                    offsetX = startOffsetX;
                    offsetY = startOffsetY;
                    for (int j = 0; j < (block)->cellLength; j++) {
                        if ((block)->rotations[0][j] == 1) {
                            DrawRectangle(offsetX, offsetY, tileWidth, tileWidth, RED);
                        } else {
                            DrawRectangle(offsetX, offsetY, tileWidth, tileWidth, BLUE);
                        }
                        offsetX += tileWidth+1;
                        if (j+1 == (block)->cellLength) break;
                        if ((j+1) % (block)->colLength == 0) {
                            offsetX = startOffsetX;
                            offsetY += tileWidth+1;
                        }
                    }
                    if ((i+1) % 2 == 0) {
                        startOffsetX = originalOffsetX;
                        originalOffsetY = offsetY + (tileWidth)*3;
                    } else {
                        startOffsetX += (offsetX-originalOffsetX)+tileWidth;
                    }
                    startOffsetY = originalOffsetY;
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
                for (int i = 0; i < (currentBlock)->cellLength; i++) {
                    if ((currentBlock)->rotations[currentRotation%(currentBlock)->rotationLength][i] == 1) {
                        DrawRectangle(offsetX, offsetY, tileWidth, tileWidth, RED);
                    }
                    offsetX += tileWidth+1;
                    if ((i+1) % (currentBlock)->colLength == 0) {
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
