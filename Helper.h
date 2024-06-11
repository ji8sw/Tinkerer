#pragma once
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