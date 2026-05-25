#pragma once

#include <functional>
#include <memory>

#include "Maths/Color.h"

using std::function;
using std::shared_ptr;
using std::weak_ptr;

using Gdiplus::Graphics;

typedef function<void(float)> UpdateFnc;
typedef function<void(Graphics*)> RenderFnc;

namespace Jamlib
{
	using Maths::Color;

	class Window
	{
		friend class Application;

		struct PrivateKey
		{
			PrivateKey() = default;
		};

		struct Deleter
		{
			void operator()(const Window* window) const;
		};

	public:
		Window(PrivateKey, int w, int h, const char* title, Color clrColor, UpdateFnc updateFnc,
		       RenderFnc renderFnc);
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;

	public:
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

	private:
		static shared_ptr<Window> m_instance;

	private:
		static void Create(int w, int h, const char* title, Color clrColor, const UpdateFnc& updateFnc, const RenderFnc& renderFnc);

		static weak_ptr<Window> Instance();

		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		int m_width;
		int m_height;
		wchar_t* m_title;
		Color m_clrColor;

		HWND m_hwnd;
		HDC m_hdc;
		PAINTSTRUCT m_ps;
		ULONG_PTR m_gdiPlusToken;
		Graphics* m_graphics;

		UpdateFnc m_update;
		RenderFnc m_render;

	private:
		void Open();
		void Close() const;

		void BeginDrawing();
		void Clear() const;
		void EndDrawing();

		bool IsWindowReady() const;

	};
}
