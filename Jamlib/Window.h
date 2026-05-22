#pragma once

#include <memory>

#include "Maths/Color.h"

using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;

using Gdiplus::Graphics;

namespace Jamlib
{
	using Maths::Color;

	class Window
	{
		struct PrivateKey
		{
			PrivateKey() = default;
		};

		struct Deleter
		{
			void operator()(Window* window) const;
		};

	public:
		static void Create(int w, int h, const char* title, Color clrColor);

		static shared_ptr<Window> Instance();

	public:
		Window(PrivateKey, int w, int h, const char* title, Color clrColor);
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;

	public:
		void Open();
		void Close();

		void BeginDrawing();
		void Clear() const;
		void EndDrawing();

		bool IsWindowReady() const;

	public:
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

	private:
		static unique_ptr<Window, Deleter> m_instance;

	private:
		int m_width;
		int m_height;
		wchar_t* m_title;
		Color m_clrColor;

		HWND m_hwnd;
		HDC m_hdc;
		PAINTSTRUCT m_ps;
		Graphics* m_graphics;

	};
}
