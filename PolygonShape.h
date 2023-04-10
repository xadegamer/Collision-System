#pragma once

#include "Vec2.h"

#include <vector>

using namespace CollisionSystem;

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

		static std::vector<Vec2> GetPolygon( PolygonShapeType polygonShapeType, float radius);

		static std::vector<Vec2> GetRandomPolygon(float radius);

};

