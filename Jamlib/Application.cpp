#include "Application.h"

#include "Window.h"

namespace Jamlib
{
	shared_ptr<Application> Application::m_instance;

	shared_ptr<Window> Application::GetWindow()
	{
		return m_instance->m_window;
	}

	Application::Application(const int w, const int h, const char* title, const Color clrColor)
	{
		Window::Create(w, h, title, clrColor,
			[](const float dt)
			{
				m_instance->OnTick(dt);
			},
			[](Graphics* graphics)
			{
				m_instance->OnRender(graphics);
			}
		);

		m_window = Window::Instance().lock();
	}

	Application::~Application() = default;

	void Application::Run()
	{
		if (m_window)
		{
			m_instance = shared_ptr<Application>(this);

			m_window->Open();

			if (m_window->IsWindowReady())
			{
				MSG msg = {};
				bool shouldBreak = false;

				while (GetMessage(&msg, nullptr, 0, 0) && !shouldBreak)
				{
					MSG peeked = {};
					while (PeekMessage(&peeked, nullptr, 0, 0, PM_REMOVE))
					{
						if (peeked.message == WM_QUIT)
						{
							shouldBreak = true;
							break;
						}
					}

					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	}
}
