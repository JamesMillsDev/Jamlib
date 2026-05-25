#include "Window.h"

using Gdiplus::GdiplusStartupInput;

namespace Jamlib
{
	shared_ptr<Window> Window::m_instance;

	void Window::Deleter::operator()(const Window* window) const
	{
		delete window;
	}

	void Window::Create(const int w, const int h, const char* title, const Color clrColor, const UpdateFnc& updateFnc, const RenderFnc& renderFnc)
	{
		if (m_instance)
		{
			return;
		}

		m_instance = shared_ptr<Window>(new Window{ PrivateKey{}, w, h, title, clrColor, updateFnc, renderFnc }, Deleter{});
	}

	weak_ptr<Window> Window::Instance()
	{
		return m_instance;
	}

	Window::Window(PrivateKey, const int w, const int h, const char* title, const Color clrColor, UpdateFnc updateFnc,
	               RenderFnc renderFnc) :
		m_width{ w }, m_height{ h }, m_title{ new wchar_t[strlen(title) + 1] },
		m_clrColor{ clrColor }, m_hwnd{ nullptr }, m_hdc{ nullptr }, m_ps{ }, m_gdiPlusToken{ 0 },
		m_graphics{ nullptr }, m_update{ std::move(updateFnc) }, m_render{ std::move(renderFnc) }
	{
		MultiByteToWideChar(
			CP_UTF8, 0, title, static_cast<int>(strlen(title) + 1), m_title, static_cast<int>(strlen(title) + 1)
		);
	}

	Window::~Window()
	{
		delete[] m_title;
		m_title = nullptr;
	}

	void Window::Open()
	{
		constexpr wchar_t className[] = L"Jamlib Window Class";

		const HINSTANCE hInstance = GetModuleHandle(nullptr);

		WNDCLASS wc = {};
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = className;
		RegisterClass(&wc);

		const GdiplusStartupInput gdiPlusStartupInput;

		if (Gdiplus::GdiplusStartup(&m_gdiPlusToken, &gdiPlusStartupInput, nullptr) != Gdiplus::Ok)
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

		ShowWindow(m_hwnd, 1);
		UpdateWindow(m_hwnd);
	}

	void Window::Close() const
	{
		Gdiplus::GdiplusShutdown(m_gdiPlusToken);
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

	LRESULT Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
			case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
			case WM_PAINT:
			{
				m_instance->BeginDrawing();
				m_instance->Clear();

				Graphics* graphics = m_instance->m_graphics;
				m_instance->m_render(graphics);

				m_instance->EndDrawing();
				return 0;
			}

			default:
			{
				return DefWindowProc(hwnd, uMsg, wParam, lParam);
			}
		}
	}
}
