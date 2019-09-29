//
// Created by Joker on 8/17/2018.
//

#include <iostream>
#include <cstring>
#include <Application/Application.hpp>

using namespace std;


int main(int argc, char** argv)
{
    if (g_pApp == nullptr) {
        cout << "ERROR : g_pApp is nullptr!" << endl;
        return -1;
    }

    g_pApp->Initialize(argc, argv);

    // Create window with window options
    WindowOptions wo;
    memset(&wo, 0, sizeof(WindowOptions));
    wo.fullScreen = false;
    wo.size.x     = 1024;
    wo.size.y     = 768;
    wo.title      = "Test window";

    g_pApp->SetupWindow(&wo);
    g_pApp->Run();

    g_pApp->Destroy();

    return 0;
}