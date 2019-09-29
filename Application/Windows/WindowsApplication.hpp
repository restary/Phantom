//
// Created by Joker on 8/17/2018.
//

#pragma once


#include <Windows.h>
#include "../Application.hpp"


class WindowsApplication : public Application
{
public:
    int Initialize(int argc, char** argv) override;
    virtual int SetupWindow(const WindowOptions *pOptions) override;
    virtual int Run() override;
    virtual void Destroy() override;

private:
    const static char* WIN_CLASS_NAME;

    HWND      m_hWnd;
    HINSTANCE m_hInstance;
};
