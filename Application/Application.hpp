//
// Created by Joker on 8/20/2018.
//

#pragma once

#include <Math.hpp>
#include <Render/RenderSystem.hpp>

using namespace PhantomEngine::Math;
using namespace PhantomEngine::Render;


struct WindowOptions
{
    Vector2     size;
    bool        fullScreen;
    const char* title;
};


class Application
{
public:
    virtual int Initialize(int argc, char** argv);
    virtual int SetupWindow(const WindowOptions *pOptions);
    virtual int Run() = 0;
    virtual void Destroy() = 0;

    static RenderSystem* renderSystem;

protected:
    int           m_Argc;
    char**        m_Argv;
    WindowOptions m_WindowOptions;
};

extern Application* g_pApp;
