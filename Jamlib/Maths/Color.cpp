#include "Color.h"

#include <format>

enum : uint8
{
	RedOffset = 24,
	GreenOffset = 16,
	BlueOffset = 8,
	AlphaOffset = 0,
};

enum : uint32
{
	RedMask = 0x00ffffff,
	GreenMask = 0xff00ffff,
	BlueMask = 0xffff00ff,
	AlphaMask = 0xffffff00,
};

namespace Jamlib::Maths
{
	const Color Color::LIGHT_GRAY = 0xC8C8C8FF;
	const Color Color::GRAY = 0x828282FF;
	const Color Color::DARK_GRAY = 0x505050FF;
	const Color Color::YELLOW = 0xFDF900FF;
	const Color Color::GOLD = 0xFFCB00FF;
	const Color Color::ORANGE = 0xFFA100FF;
	const Color Color::PINK = 0xFF6DC2FF;
	const Color Color::RED = 0xE62937FF;
	const Color Color::MAROON = 0xBE2137FF;
	const Color Color::GREEN = 0x00E430FF;
	const Color Color::LIME = 0x009E2FFF;
	const Color Color::DARK_GREEN = 0x00752CFF;
	const Color Color::SKY_BLUE = 0x66BFFFFF;
	const Color Color::BLUE = 0x0079F1FF;
	const Color Color::DARK_BLUE = 0x0052ACFF;
	const Color Color::PURPLE = 0xC87AFFFF;
	const Color Color::VIOLET = 0x873CBEFF;
	const Color Color::DARK_PURPLE = 0x701F7EFF;
	const Color Color::BEIGE = 0xD3B083FF;
	const Color Color::BROWN = 0x7F6A4FFF;
	const Color Color::DARK_BROWN = 0x4C3F2FFF;

	const Color Color::WHITE = 0xFFFFFFFF;
	const Color Color::BLACK = 0x000000FF;
	const Color Color::CLEAR = 0x00000000;
	const Color Color::MAGENTA = 0xFF00FFFF;

	Color::Color()
		: m_value{ 0x000000ff }
	{}

	Color::Color(const uint32 value)
		: m_value{ value }
	{}

	Color::Color(const uint8 r, const uint8 g, const uint8 b, const uint8 a)
		: m_value{
			static_cast<uint32>(r << RedOffset) |
			static_cast<uint32>(g << GreenOffset) |
			static_cast<uint32>(b << BlueOffset) |
			static_cast<uint32>(a << AlphaOffset)
		}
	{

	}

	uint8 Color::Red() const
	{
		return static_cast<uint8>(m_value >> RedOffset);
	}

	void Color::SetRed(const uint8 red)
	{
		m_value = (m_value & RedMask) | (static_cast<uint32>(red << RedOffset));
	}

	uint8 Color::Green() const
	{
		return static_cast<uint8>(m_value >> GreenOffset);
	}

	void Color::SetGreen(const uint8 green)
	{
		m_value = (m_value & GreenMask) | (static_cast<uint32>(green << GreenOffset));
	}

	uint8 Color::Blue() const
	{
		return static_cast<uint8>(m_value >> BlueOffset);
	}

	void Color::SetBlue(const uint8 blue)
	{
		m_value = (m_value & BlueMask) | (static_cast<uint32>(blue << BlueOffset));
	}

	uint8 Color::Alpha() const
	{
		return static_cast<uint8>(m_value >> AlphaOffset);
	}

	void Color::SetAlpha(const uint8 alpha)
	{
		m_value = (m_value & AlphaMask) | (static_cast<uint32>(alpha << AlphaOffset));
	}

	SolidBrush Color::ToBrush() const
	{
		return { Gdiplus::Color(Alpha(), Red(), Green(), Blue()) };
	}

	ostream& operator<<(ostream& stream, const Color& color)
	{
		stream << std::format(
		                      "(r:{}, g:{}, b:{}, a:{})", 
		                      color.Red(), color.Blue(), 
		                      color.Green(), color.Alpha()
		                     );

		return stream;
	}

	bool Color::operator==(const Color& rhs) const
	{
		return m_value == rhs.m_value;
	}

	bool Color::operator!=(const Color& rhs) const
	{
		return m_value != rhs.m_value;
	}
}
