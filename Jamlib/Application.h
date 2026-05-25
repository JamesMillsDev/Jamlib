#pragma once

#include <memory>

#include "Maths/Color.h"

using std::shared_ptr;

using Gdiplus::Graphics;

namespace Jamlib
{
	class Window;
	using Maths::Color;

	class Application
	{
	public:
		static shared_ptr<Window> GetWindow();

	public:
		Application(int w, int h, const char* title, Color clrColor);
		virtual ~Application();

	public:
		void Run();

	protected:
		virtual void OnOpen() {}
		virtual void OnClose() {}

		virtual void OnRender(Graphics* graphics) {}
		virtual void OnTick(float dt) {}

	private:
		static shared_ptr<Application> m_instance;

	private:
		shared_ptr<Window> m_window;

	};
}
