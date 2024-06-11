#include "raylib.h"

float PercentageOf(float Percentage, float Value)
{
    return (Value * Percentage) / 100;
}

int main()
{
    const int Width = 800;
    const int Height = 450;
    InitWindow(Width, Height, "Tinkerer");
    SetWindowState(FLAG_WINDOW_UNDECORATED);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(Color{ 41, 46, 61, 255 });

        Rectangle Foreground = { 0, 0, Width, PercentageOf(8, Height) }; // pos then size
        bool MouseOverForeground = CheckCollisionPointRec(GetMousePosition(), Foreground);
        bool ClickForeground = MouseOverForeground && IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT);
        DrawRectangleRec(Foreground, Color{ 49, 55, 73, 255 });

        Rectangle QuitButtonBG = { PercentageOf(95.5, Width), 0, PercentageOf(8, Height), PercentageOf(8, Height) };
        bool MouseOverQuit = CheckCollisionPointRec(GetMousePosition(), QuitButtonBG);
        bool ClickedQuit = MouseOverQuit && IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT);
        DrawRectangleRec(QuitButtonBG, MouseOverQuit ? Color{ 255 , 46, 61, 255 } : Color{ 49, 55, 73, 255 });
        Vector2 TextSize = MeasureTextEx(GetFontDefault(), "x", 40, 1.0f);
        float TextX = QuitButtonBG.x + (QuitButtonBG.width - TextSize.x) / 2;
        float TextY = QuitButtonBG.y + (QuitButtonBG.height - TextSize.y) / 2;
        DrawText("x", TextX, TextY, 40, WHITE);

        if (ClickedQuit)
            break;

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
