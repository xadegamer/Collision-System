#include "PolygonShape.h"
#include <stdlib.h>

std::vector<Vector2> PolygonShape::GetPolygon(PolygonShapeType polygonShapeType, float radius)
{
	std::vector<Vector2> vertices;

	switch (polygonShapeType)
	{
	case PolygonShapeType::TRIANGLE:
		vertices.push_back(Vector2(0, -radius));
		vertices.push_back(Vector2(radius, radius));
		vertices.push_back(Vector2(-radius, radius));
		break;
	case PolygonShapeType::SQUARE:
		vertices.push_back(Vector2(-radius, -radius));
		vertices.push_back(Vector2(radius, -radius));
		vertices.push_back(Vector2(radius, radius));
		vertices.push_back(Vector2(-radius, radius));
		break;
	case PolygonShapeType::PENTAGON:
		vertices.push_back(Vector2(0, -radius));
		vertices.push_back(Vector2(radius, -radius / 2));
		vertices.push_back(Vector2(radius, radius / 2));
		vertices.push_back(Vector2(0, radius));
		vertices.push_back(Vector2(-radius, radius / 2));
		vertices.push_back(Vector2(-radius, -radius / 2));
		break;
	case PolygonShapeType::HEXAGON:
		vertices.push_back(Vector2(0, -radius));
		vertices.push_back(Vector2(radius, -radius / 2));
		vertices.push_back(Vector2(radius, radius / 2));
		vertices.push_back(Vector2(0, radius));
		vertices.push_back(Vector2(-radius, radius / 2));
		vertices.push_back(Vector2(-radius, -radius / 2));
		break;
	case PolygonShapeType::OCTAGON:
		vertices.push_back(Vector2(0, -radius));
		vertices.push_back(Vector2(radius, -radius / 2));
		vertices.push_back(Vector2(radius, radius / 2));
		vertices.push_back(Vector2(0, radius));
		vertices.push_back(Vector2(-radius, radius / 2));
		vertices.push_back(Vector2(-radius, -radius / 2));
		break;
	default:
		break;
	}

	return vertices;
}

std::vector<Vector2> PolygonShape::GetRandomPolygon(float radius)
{
	return GetPolygon((PolygonShapeType)(rand() % 5), radius);
}
