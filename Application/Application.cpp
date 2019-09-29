//
// Created by Joker on 8/20/2018.
//

#include "Application.hpp"

RenderSystem* Application::renderSystem = nullptr;


int Application::Initialize(int argc, char **argv)
{
    m_Argc = argc;
    m_Argv = argv;

    return 0;
}


int Application::SetupWindow(const WindowOptions *pOptions)
{
    m_WindowOptions = *pOptions;

    return 0;
}