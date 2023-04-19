#pragma once

#include "Vec2.h"

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

		/// <summary>
		/// Generates and returns a polygon with the specified shape and radius.
		/// </summary>
		/// <param name="polygonShapeType">The type of polygon shape to generate</param>
		/// <param name="radius">The radius of the polygon</param>
		/// <returns>A vector of Vec2 objects representing the points of the generated polygon</returns>
		static std::vector<Vec2> GetPolygon( PolygonShapeType polygonShapeType, float radius);

		/// <summary>
		/// Generates and returns a random polygon with the specified radius.
		/// </summary>
		/// <param name="radius">The radius of the polygon</param>
		/// <returns>A vector of Vec2 objects representing the points of the generated polygon</returns>
		static std::vector<Vec2> GetRandomPolygon(float radius);

};

