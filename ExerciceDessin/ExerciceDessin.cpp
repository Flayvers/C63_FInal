#include <iostream>
#include <raylib.h>

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;
    const int nbrSymbolX = 10;
    const int nbrSymbolY = 10;
    Vector2 pacmanPos = { screenWidth / 4.0f, screenHeight / 2.0f };

    bool pacMan = true;

    const float gridSpacingX = 800.0f / 11.0f;
    const float gridSpacingY = 800.0f / 12.0f;

    InitWindow(screenWidth, screenHeight, "Exercice Dessin");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (pacMan)
        {
            BeginDrawing();

            ClearBackground(BLACK);

            DrawCircleSector(pacmanPos, 90.0f, 35.0f, 325.0f, 1000, YELLOW);
            DrawCircle(380, (screenHeight / 2), 35.0f, LIGHTGRAY);
            DrawCircle(485, (screenHeight / 2), 35.0f, LIGHTGRAY);
            DrawCircle(590, (screenHeight / 2), 35.0f, LIGHTGRAY);
            DrawText("Waka waka!", 100, 500, 45, RAYWHITE);

            EndDrawing();
        }
        else
        {
            BeginDrawing();
            ClearBackground(VIOLET);

            // Draw grid pattern
            for (int y = 0; y < screenHeight; y += (gridSpacingY * 3))
            {
                for (int x = 0; x < screenWidth; x += gridSpacingX)
                {
                    DrawCircle(x, y, 6, PURPLE);
                    DrawRectangle(x + (gridSpacingX / 3), y + (gridSpacingY), 6, 6, PURPLE);
                    DrawText("!", x + (gridSpacingX / 2) + 10, y + (gridSpacingY * 2), 6, PURPLE);
                }
            }

            DrawText("Loading...", screenWidth / 4.0f, screenHeight / 2.5f, 90, YELLOW);

            EndDrawing();
        }
        if (IsKeyPressed(KEY_SPACE))
        {
            pacMan = !pacMan;
        }





    }
    CloseWindow();

    return 0;
}
