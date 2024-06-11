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
#include "raylib.h"
#include <string>
#include <vector>
#ifdef NDEBUG
#else
#define DBG
#include <iostream>
#endif

float PercentageOf(float Percentage, float Value)
{
    return (Value * Percentage) / 100;
}

char KeyToChar(int Key)
{
    switch (Key)
    {
    case KEY_A:
        return 'a';
        break;
    case KEY_B:
        return 'b';
        break;
    case KEY_C:
        return 'c';
        break;
    case KEY_D:
        return 'd';
        break;
    case KEY_E:
        return 'e';
        break;
    case KEY_F:
        return 'f';
        break;
    case KEY_G:
        return 'g';
        break;
    case KEY_H:
        return 'h';
        break;
    case KEY_I:
        return 'i';
        break;
    case KEY_J:
        return 'j';
        break;
    case KEY_K:
        return 'k';
        break;
    case KEY_L:
        return 'l';
        break;
    case KEY_M:
        return 'm';
        break;
    case KEY_N:
        return 'n';
        break;
    case KEY_O:
        return 'o';
        break;
    case KEY_P:
        return 'p';
        break;
    case KEY_Q:
        return 'q';
        break;
    case KEY_R:
        return 'r';
        break;
    case KEY_S:
        return 's';
        break;
    case KEY_T:
        return 't';
        break;
    case KEY_U:
        return 'u';
        break;
    case KEY_V:
        return 'v';
        break;
    case KEY_W:
        return 'w';
        break;
    case KEY_X:
        return 'x';
        break;
    case KEY_Y:
        return 'y';
        break;
    case KEY_Z:
        return 'z';
        break;
    case KEY_SPACE:
        return ' ';
        break;
    default:
        return 'a';
    }
}

int GetAnyKeyDown()
{
    for (int Key = KEY_SPACE; Key < 350; Key++)  // Assuming 350 is the upper limit for key codes
    {
        if (IsKeyReleased(Key))
        {
            return Key;
            break;
        }
    }

    return 0;
}

int main()
{
    const int Width = 800;
    const int Height = 450;
    bool WordWrap = true;
    InitWindow(Width, Height, "Tinkerer");
    SetWindowState(FLAG_WINDOW_UNDECORATED);

    std::vector<std::string> Lines = { "" };
    Vector2 CursorPosition = { 0, 0 };

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

        if (IsWindowFocused() && !ClickForeground && !ClickedQuit) // text box is focused
        {
            std::string Characters = Lines[CursorPosition.y];
            int KeyDown = GetAnyKeyDown();
            if (KeyDown != 0)
            {
                if (KeyDown == KEY_BACKSPACE)
                {
                    if (CursorPosition.x == 1 && CursorPosition.y != 0)
                    {
                        CursorPosition.y -= 1;
                        CursorPosition.x = Lines[CursorPosition.y].size();
                        Characters = Lines[CursorPosition.y];
                        Characters.pop_back();
                    }
                    else if (CursorPosition.x > 1)
                    {
                        CursorPosition.x = Lines[CursorPosition.y].size();
                        Characters.pop_back();
                    }
                }
                else if (KeyDown == KEY_ENTER)
                {
                    CursorPosition.y += 1;
                    if (Lines.size() <= CursorPosition.y)
                        Lines.push_back("");
                    Characters = Lines[CursorPosition.y];
                }
                else
                {
                    char NewChar = KeyToChar(KeyDown);
                    if (WordWrap)
                    {
                        int TextWidth = MeasureText((Characters + NewChar).c_str(), 40);
#ifdef DBG
                        std::cout << "width: " << std::to_string(TextWidth) << "\nCharacters: " << Characters << std::endl;
#endif
                        if (TextWidth > Width)
                        {
                            CursorPosition.y += 1;
                            if (Lines.size() <= CursorPosition.y)
                                Lines.push_back("");
                            Characters = Lines[CursorPosition.y];
                        }
                    }


                    Characters = Characters + KeyToChar(KeyDown);
                    CursorPosition.x += 1;
                }
            }
            Lines[CursorPosition.y] = Characters; // update line
        }

        for (int Index = 0; Index < Lines.size(); Index++)
            DrawText(Lines[Index].c_str(), 1, PercentageOf(10, Height) * (Index + 1), 40, WHITE);

        if (ClickedQuit)
            break;

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
