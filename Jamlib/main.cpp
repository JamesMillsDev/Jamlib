#include <iostream>
#include <windows.h>
#include <gdiplus.h>

#include "Window.h"
#include "Maths/Color.h"
//using namespace Gdiplus;

//void DrawRectangle(HDC hdcDest, int x, int y, int width, int height, Jamlib::Maths::Color color)
//{
//    Graphics graphics(hdcDest);
//    // GDI+ Color uses ARGB order
//    SolidBrush brush = color.ToBrush();
//    graphics.FillRectangle(&brush, x, y, width, height);
//}
//
//// 1. The Window Procedure (handles events)
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    switch (uMsg)
//    {
//        case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hwnd, &ps);
//
//            // All painting occurs here, between BeginPaint and EndPaint.
//
//            HBRUSH hbrush = CreateSolidBrush(0xf0f0f0);
//
//            FillRect(hdc, &ps.rcPaint, hbrush);
//
//            DrawRectangle(hdc, 0, 0, 50, 50, 0xff000080);
//            DrawRectangle(hdc, 25, 25, 50, 50, 0xff000080);
//
//            DeleteObject(hbrush);
//
//            EndPaint(hwnd, &ps);
//        }
//        return 0;
//    }
//
//	if (uMsg == WM_DESTROY)
//	{
//		PostQuitMessage(0); return 0;
//	}
//	return DefWindowProc(hwnd, uMsg, wParam, lParam);
//}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrev, PWSTR pCmdLine, int nCmdShow)
{
    //// 2. Register Class
    //constexpr wchar_t className[] = L"Sample Window Class";
    //WNDCLASS wc = { };
    //wc.lpfnWndProc = WindowProc;
    //wc.hInstance = hInstance;
    //wc.lpszClassName = className;
    //RegisterClass(&wc);

    //GdiplusStartupInput gdiplusStartupInput;
    //ULONG_PTR           gdiplusToken;


    //GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    //// 3. Create Window
    //HWND hwnd = CreateWindowEx(0, className, L"Learn WinAPI", WS_OVERLAPPEDWINDOW,
    //    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    //    nullptr, nullptr, hInstance, nullptr);

    //if (hwnd == nullptr)
    //{
	   // return 0;
    //}

    //ShowWindow(hwnd, nCmdShow);
    Jamlib::Window::Create(800, 600, "Fuck WINAPI", Jamlib::Maths::Color::BLACK);

    shared_ptr win = Jamlib::Window::Instance();
    win->Open();

    // 4. Message Loop
    MSG msg = { };
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}