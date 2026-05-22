#include <iostream>
#include <windows.h>

#include "Window.h"
#include "Maths/Color.h"

using Jamlib::Window;

#if _DEBUG
#include <crtdbg.h>
#endif

int x = 0, y = 0, w = 50, h = 50;

void Render(Graphics* graphics)
{
    SolidBrush b = Jamlib::Maths::Color::RED.ToBrush();
    graphics->FillRectangle(&b, x, y, w, h);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrev, PWSTR pCmdLine, int nCmdShow)
{
#if _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    Window::Create(800, 600, "Fuck WINAPI", Jamlib::Maths::Color::BLACK, nullptr, &Render);

    if (const shared_ptr win = Window::Instance().lock())
    {
        win->Open();

        if (win->IsWindowReady())
        {
            MSG msg = { };
            while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                if (msg.message == WM_QUIT)
                {
                    break;
                }

                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    return 0;
}