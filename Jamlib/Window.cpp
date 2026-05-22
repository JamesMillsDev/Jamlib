#include "Window.h"

using Gdiplus::GdiplusStartupInput;

namespace Jamlib
{
	unique_ptr<Window, Window::Deleter> Window::m_instance;

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
			case WM_PAINT:
			{

				return 0;
			}

			case WM_DESTROY:
			{
				PostQuitMessage(0); 
				return 0;
			}

			default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	void Window::Deleter::operator()(Window* window) const
	{
		delete window;
	}

	void Window::Create(int w, int h, const char* title, Color clrColor)
	{
		if (m_instance)
		{
			return;
		}

		m_instance = unique_ptr<Window, Deleter>(new Window{ PrivateKey{}, w, h, title, clrColor }, Deleter{});
	}

	shared_ptr<Window> Window::Instance()
	{
		return shared_ptr<Window>(m_instance.get());
	}

	Window::Window(PrivateKey, const int w, const int h, const char* title, const Color clrColor) :
		m_width{ w }, m_height{ h }, m_title{ new wchar_t[strlen(title) + 1] },
		m_clrColor{ clrColor }, m_hwnd{ nullptr }, m_hdc{ nullptr }, m_ps{},
		m_graphics{ nullptr }
	{
		MultiByteToWideChar(CP_UTF8, 0, title, -1, m_title, static_cast<int>(strlen(title) + 1));
	}

	Window::~Window()
	{
		delete[] m_title;
		m_title = nullptr;
	}

	void Window::Open()
	{
		constexpr wchar_t className[] = L"Jamlib Window Class";

		HINSTANCE hInstance = GetModuleHandle(nullptr);

		WNDCLASS wc = {};
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = className;
		RegisterClass(&wc);

		GdiplusStartupInput gdiPlusStartupInput;
		ULONG_PTR gdiPlusToken;

		if (Gdiplus::GdiplusStartup(&gdiPlusToken, &gdiPlusStartupInput, nullptr) != Gdiplus::Ok)
		{
			return;
		}

		m_hwnd = CreateWindowEx(
			0, className, m_title, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, m_width, m_height,
			nullptr, nullptr, hInstance, nullptr
		);

		if (m_hwnd == nullptr)
		{
			return;
		}

		ShowWindow(m_hwnd, 2);
	}

	void Window::Close()
	{
		// Cry
	}

	void Window::BeginDrawing()
	{
		m_hdc = BeginPaint(m_hwnd, &m_ps);
		m_graphics = new Graphics{ m_hdc };
	}

	void Window::Clear() const
	{
		const HBRUSH bgBrush = CreateSolidBrush(
			RGB(m_clrColor.Red(), m_clrColor.Blue(), m_clrColor.Green())
		);

		FillRect(m_hdc, &m_ps.rcPaint, bgBrush);
	}

	void Window::EndDrawing()
	{
		EndPaint(m_hwnd, &m_ps);

		delete m_graphics;
		m_graphics = nullptr;
	}

	bool Window::IsWindowReady() const
	{
		return m_hwnd != nullptr;
	}
}
