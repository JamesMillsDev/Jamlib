#include <iostream>
#include <windows.h>

#include "Application.h"

#include "Maths/Color.h"

using Jamlib::Application;

#if _DEBUG
#include <crtdbg.h>
#endif

//int x = 0, y = 0, w = 50, h = 50;
//
//void Render(Graphics* graphics)
//{
//    SolidBrush b = Jamlib::Maths::Color::RED.ToBrush();
//    graphics->FillRectangle(&b, x, y, w, h);
//}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrev, PWSTR pCmdLine, int nCmdShow)
{
#if _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    shared_ptr<Application> app = std::make_shared<Application>(800, 600, "Test Window", Jamlib::Maths::Color::BLACK);
    app->Run();

    return 0;
}