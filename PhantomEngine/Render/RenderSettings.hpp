//
// Created by Joker on 8/28/2018.
//

#pragma once

#include <Math.hpp>
#ifdef WINDOWS
#include <Windows.h>
#endif

using namespace PhantomEngine::Math;


namespace PhantomEngine::Render
{
    struct RenderSettings
    {
        Vector2 windowSize;
#ifdef WINDOWS
        HWND hwnd;
#endif
    };
}
