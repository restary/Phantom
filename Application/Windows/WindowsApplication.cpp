#include "WindowsApplication.hpp"

#include <tchar.h>
#include <Debug.hpp>
#include <Render/RenderSystem.hpp>

using namespace PhantomEngine;


// Global application instance
Application* g_pApp = new WindowsApplication();


// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
                            UINT message,
                            WPARAM wParam,
                            LPARAM lParam);

const char* WindowsApplication::WIN_CLASS_NAME = "Phantom Window";


int WindowsApplication::Initialize(int argc, char** argv)
{
    Application::Initialize(argc, argv);

	Debug::Log("Start to initialize windows application...");
    WNDCLASS wc;
    int atom;

    /* What we need to do is to initialize the fgDisplay global structure here. */
    m_hInstance = GetModuleHandle(NULL);
    atom = GetClassInfo(m_hInstance, _T(WIN_CLASS_NAME), &wc);
    if (atom == 0) {
        ZeroMemory(&wc, sizeof(WNDCLASS));

        /*
         * Each of the windows should have its own device context, and we
         * want redraw events during Vertical and Horizontal Resizes by
         * the user.
         */
        wc.lpfnWndProc   = WindowProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = m_hInstance;
        wc.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
//        wc.hIcon         = LoadIcon( fgDisplay.pDisplay.Instance, _T("GLUT_ICON") );
//        if (!wc.hIcon)
//            wc.hIcon     = LoadIcon( NULL, IDI_WINLOGO );
//        wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
        wc.hbrBackground = NULL;
        wc.lpszMenuName  = NULL;
        wc.lpszClassName = _T(WIN_CLASS_NAME);

        /* Register the window class */
        atom = RegisterClass(&wc);
        if (atom == 0) {
            Debug::Error("Register window class failed");
        }
    }

    return atom;
}


int WindowsApplication::SetupWindow(const WindowOptions *pOptions)
{
    Application::SetupWindow(pOptions);

    // create the window and use the result as the handle
    m_hWnd = CreateWindowEx(0,
                            WIN_CLASS_NAME,                         // name of the window class
                            _T(pOptions->title),                    // title of the window
                            WS_OVERLAPPEDWINDOW,                    // window style
                            0,                                      // x-position of the window
                            0,                                      // y-position of the window
                            static_cast<int>(pOptions->size.x),     // width of the window
                            static_cast<int>(pOptions->size.y),     // height of the window
                            nullptr,                                // we have no parent window, NULL
                            nullptr,                                // we aren't using menus, NULL
                            m_hInstance,                            // application handle
                            nullptr);                               // used with multiple windows, NULL
    if (m_hWnd == 0) {
        Debug::Error("Create window failed.");
        return -1;
    }

    ShowWindow(m_hWnd, SW_SHOWNORMAL);

    // Setup render system
    RenderSettings settings;
    ZeroMemory(&settings, sizeof(RenderSettings));
    settings.hwnd = m_hWnd;
    settings.windowSize = pOptions->size;

    renderSystem = new RenderSystem();
    renderSystem->Initialize(&settings);

    return 0;
}


int WindowsApplication::Run()
{
    // this struct holds Windows event messages
    MSG msg;

    // wait for the next message in the queue, store the result in 'msg'
    while(GetMessage(&msg, nullptr, 0, 0)) {
        // translate keystroke messages into the right format
        TranslateMessage(&msg);

        // send the message to the WindowProc function
        DispatchMessage(&msg);
    }

    return 0;
}


void WindowsApplication::Destroy()
{

}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch(message)
    {
        case WM_CREATE:
            break;
        case WM_PAINT:
            if (Application::renderSystem != nullptr) {
                Application::renderSystem->Render();
            }
            break;
        // this message is read when the window is closed
        case WM_DESTROY:
            if (Application::renderSystem != nullptr) {
                delete Application::renderSystem;
            }

            // close the application entirely
            PostQuitMessage(0);
            return 0;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}