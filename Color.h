#pragma once

#include <SDL.h>

enum class ColorType
{
	White,
	Red,
	Green,
	Blue,
	Yellow,
	Orange,
	Purple,
	Pink,
	Gray,
	LightGray,
	DarkGray,
	LightBlue,
	LightGreen,
	LightRed,
	LightYellow,
	LightOrange,
	LightPurple,
	LightPink,
	LightBrown,
	DarkBlue,
	DarkGreen,
	DarkRed,
	DarkYellow,
	DarkOrange,
	DarkPurple,
	DarkPink,
	DarkBrown,
	Black,
	Transparent
};

class Color
{
public:

	static SDL_Color GetColor(ColorType colorType);

	static SDL_Color GetRandomColor();
};

