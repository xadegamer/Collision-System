#include "PolygonCollider.h"

PolygonCollider::PolygonCollider(void* owner, Vector2 nextPosition, std::vector<Vector2> _points, bool isStatic) : Collider(owner, nextPosition, isStatic)
{
	points = _points;
	num_points = points.size();
	UpdatePosition(nextPosition);
}

void PolygonCollider::UpdatePosition(Vector2 nextPosition)
{
	position = nextPosition;
}

Vector2 PolygonCollider::GetCenter()
{
	Vector2 center = Vector2(0, 0);
	for (int i = 0; i < num_points; i++)
	{
		center += points[i];
	}
	center /= num_points;
	return center + position;
}

std::vector<Vector2> PolygonCollider::GetWorldPoints()
{
	std::vector<Vector2> worldPoints;
	for (int i = 0; i < num_points; i++)
	{
		worldPoints.push_back(Vector2(points[i].x + position.x, points[i].y + position.y));
	}
	return worldPoints;
}