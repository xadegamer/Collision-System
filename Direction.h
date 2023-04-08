#pragma once

#include "Vector2.h"


enum DirectionType
{
	Up,
	UpRight,
	UpLeft,
	Down,
	DownRight,
	DownLeft,
	Right,
	Left,
};

class Direction
{
	public:

	static Vector2 GetDirection(DirectionType directionType);

	static Vector2 GetRandomDirection();
};

