#pragma once
#include <Windows.h>

HWND Entryhwnd = NULL;
int processid = 0;
RECT Rect;

ULONG64 client = 0;


namespace Settings
{
    bool bMenu = true;

    namespace Visuals
    {
         bool bSnaplines = true;
         bool bDistance = false;
         bool bBox = true;
         bool bBoxOutlined = false;
         bool bHealth = false;
         bool headcircle = false;

         float BoxWidth = 1.0f;
    }
}

