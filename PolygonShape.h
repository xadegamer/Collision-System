#pragma once

#include "Vector2.h"

#include <vector>

enum class PolygonShapeType
{
	TRIANGLE,
	SQUARE,
	PENTAGON,
	HEXAGON,
	OCTAGON,
};

class PolygonShape
{
	public:

		static std::vector<Vector2> GetPolygon( PolygonShapeType polygonShapeType, float radius);

		static std::vector<Vector2> GetRandomPolygon(float radius);

};

