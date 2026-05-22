#pragma once

#include <windows.h>
#include <gdiplus.h>
#include <numerics.h>
#include <ostream>

using std::ostream;

using Gdiplus::SolidBrush;

namespace Jamlib::Maths
{
	class Color
	{
	public:
		static const Color LIGHT_GRAY;
		static const Color GRAY;
		static const Color DARK_GRAY;
		static const Color YELLOW;
		static const Color GOLD;
		static const Color ORANGE;
		static const Color PINK;
		static const Color RED;
		static const Color MAROON;
		static const Color GREEN;
		static const Color LIME;
		static const Color DARK_GREEN;
		static const Color SKY_BLUE;
		static const Color BLUE;
		static const Color DARK_BLUE;
		static const Color PURPLE;
		static const Color VIOLET;
		static const Color DARK_PURPLE;
		static const Color BEIGE;
		static const Color BROWN;
		static const Color DARK_BROWN;

		static const Color WHITE;
		static const Color BLACK;
		static const Color CLEAR;
		static const Color MAGENTA;

	public:
		Color();
		Color(uint32 value);
		Color(uint8 r, uint8 g, uint8 b, uint8 a);

		~Color() = default;
		Color(const Color&) = default;
		Color(Color&&) = default;

	public:
		[[nodiscard]] uint8 Red() const;
		void SetRed(uint8 red);

		[[nodiscard]] uint8 Green() const;
		void SetGreen(uint8 green);

		[[nodiscard]] uint8 Blue() const;
		void SetBlue(uint8 blue);

		[[nodiscard]] uint8 Alpha() const;
		void SetAlpha(uint8 alpha);

		[[nodiscard]] SolidBrush ToBrush() const;

	public:
		friend ostream& operator<<(ostream& stream, const Color& color);

		Color& operator=(const Color&) = default;
		Color& operator=(Color&&) = default;

		bool operator==(const Color&) const;
		bool operator!=(const Color&) const;

	private:
		uint32 m_value;

	};
}