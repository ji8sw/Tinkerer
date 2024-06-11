#include "Helper.h"

int main()
{
    int Width = 800;
    int Height = 450;
    bool WordWrap = true;
    bool IsMaximized = false;
    bool IsDraggingTitlebar = false;
    Vector2 DragOffset = { 0, 0 };

    InitWindow(Width, Height, "Tinkerer");
    SetWindowState(FLAG_WINDOW_UNDECORATED);
    Vector2 OldWindowPosition = GetWindowPosition();
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    std::vector<std::string> Lines = { "" };
    Vector2 CursorPosition = { 0, 0 };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{ 41, 46, 61, 255 });
        int FontSize = static_cast<int>(40 * (Height / 450.0f)); // calculate base font size

        Rectangle Foreground = { 0, 0, Width, PercentageOf(8, Height) };
        bool MouseOverForeground = CheckCollisionPointRec(GetMousePosition(), Foreground);
        bool ClickedForeground = MouseOverForeground && IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT);
        bool ReleasedForeground = IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT);
        DrawRectangleRec(Foreground, Color{ 49, 55, 73, 255 });

        Rectangle QuitButtonBG = { PercentageOf(95.5, Width), 0, PercentageOf(8, Height), PercentageOf(8, Height) };
        bool MouseOverQuit = CheckCollisionPointRec(GetMousePosition(), QuitButtonBG);
        bool ClickedQuit = MouseOverQuit && IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT);
        DrawRectangleRec(QuitButtonBG, MouseOverQuit ? Color{ 255 , 46, 61, 255 } : Color{ 49, 55, 73, 255 });
        int TextSize = MeasureText("x", 40);
        float TextX = QuitButtonBG.x + (QuitButtonBG.width - TextSize) / 2;
        float TextY = QuitButtonBG.y + (QuitButtonBG.height - FontSize) / 2;
        DrawText("x", TextX, TextY, FontSize, WHITE);

        Rectangle MinMaxButtonBG = { PercentageOf(90.5, Width), 0, PercentageOf(8, Height), PercentageOf(8, Height) };
        bool MouseOverMinMax = CheckCollisionPointRec(GetMousePosition(), MinMaxButtonBG);
        bool ClickedMinMax = MouseOverMinMax && IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT);
        if (IsMaximized)
            DrawRectangleRec(MinMaxButtonBG, MouseOverMinMax ? Color{ 200 , 200, 99, 255 } : Color{ 49, 55, 73, 255 });
        else
            DrawRectangleRec(MinMaxButtonBG, MouseOverMinMax ? Color{ 76 , 255, 99, 255 } : Color{ 49, 55, 73, 255 });
        TextSize = MeasureText("-", 40);
        TextX = MinMaxButtonBG.x + (MinMaxButtonBG.width - TextSize) / 2; // centre in button
        TextY = MinMaxButtonBG.y + (MinMaxButtonBG.height - FontSize) / 2; // centre in button
        DrawText(IsMaximized ? "-" : "+", TextX, TextY, FontSize, WHITE);

        if (ClickedForeground && !IsMaximized)
        {
            IsDraggingTitlebar = true;
            DragOffset = GetMousePosition();
            Vector2 WindowPos = GetWindowPosition();
            DragOffset.x -= WindowPos.x;
            DragOffset.y -= WindowPos.y;
        }

        if (ReleasedForeground)
            IsDraggingTitlebar = false;

        if (IsDraggingTitlebar)
        {
            Vector2 MousePosition = GetMousePosition();
            SetWindowPosition(MousePosition.x - DragOffset.x, MousePosition.y - DragOffset.y);
        }

        if (IsWindowFocused() && !ClickedForeground && !ClickedQuit && !ClickedMinMax) // text box is focused
        {
            std::string Characters = Lines[CursorPosition.y];
            int KeyDown = GetAnyKeyDown();
            if (KeyDown != 0)
            {
                switch (KeyDown)
                {
                case KEY_BACKSPACE:
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

                    break;
                }
                case KEY_ENTER:
                {
                    CursorPosition.y += 1;
                    if (Lines.size() <= CursorPosition.y)
                        Lines.push_back("");
                    Characters = Lines[CursorPosition.y];

                    break;
                }
                default:
                {
                    char NewChar = KeyToChar(KeyDown);
                    if (WordWrap)
                    {
                        int TextWidth = MeasureText((Characters + NewChar).c_str(), 40);
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

                    break;
                }
                }
            }
            Lines[CursorPosition.y] = Characters; // update line
        }

        for (int Index = 0; Index < Lines.size(); Index++)
            DrawText(Lines[Index].c_str(), 1, PercentageOf(10, Height) * (Index + 1), FontSize, WHITE);

        if (ClickedQuit)
            break;
        if (ClickedMinMax)
        {
            IsMaximized = !IsMaximized;

            if (IsMaximized)
            {
                OldWindowPosition = GetWindowPosition();

                Width = GetMonitorWidth(GetCurrentMonitor());
                Height = GetMonitorHeight(GetCurrentMonitor());

                SetWindowSize(Width, Height);
                SetWindowPosition(0, 0);
            }
            else
            {
                Width = 800;
                Height = 450;

                SetWindowSize(Width, Height);
                SetWindowPosition(OldWindowPosition.x, OldWindowPosition.y);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
