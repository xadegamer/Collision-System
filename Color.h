#pragma once

#include <SDL.h>

enum class ColorType
{
	White,
	Black = 1,
	Red = 2,
	Green = 3,
	Blue = 4,
	Yellow = 5,
	Orange = 6,
	Purple = 7,
	Pink = 8,
	Gray = 9,
	LightGray = 10,
	DarkGray = 11,
	LightBlue = 12,
	LightGreen = 13,
	LightRed = 14,
	LightYellow = 15,
	LightOrange = 16,
	LightPurple = 17,
	LightPink = 18,
	LightBrown = 19,
	DarkBlue = 20,
	DarkGreen = 21,
	DarkRed = 22,
	DarkYellow = 23,
	DarkOrange = 24,
	DarkPurple = 25,
	DarkPink = 26,
	DarkBrown = 27,
	Transparent = 28
};

class Color
{
public:

	static SDL_Color GetColor(ColorType colorType);

	static SDL_Color GetRandomColor();
};

