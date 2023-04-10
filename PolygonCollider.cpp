#include "PolygonCollider.h"

namespace CollisionSystem
{
	PolygonCollider::PolygonCollider(void* owner, Vec2 nextPosition, std::vector<Vec2> _points, bool isStatic) : Collider(owner, nextPosition, isStatic)
	{
		points = _points;
		num_points = points.size();
		UpdatePosition(nextPosition);
	}

	void PolygonCollider::UpdatePosition(Vec2 nextPosition)
	{
		position = nextPosition;
	}

	Vec2 PolygonCollider::GetCenter()
	{
		Vec2 center = Vec2(0, 0);
		for (int i = 0; i < num_points; i++)
		{
			center += points[i];
		}
		center /= num_points;
		return center + position;
	}

	std::vector<Vec2> PolygonCollider::GetWorldPoints()
	{
		std::vector<Vec2> worldPoints;
		for (int i = 0; i < num_points; i++)
		{
			worldPoints.push_back(Vec2(points[i].x + position.x, points[i].y + position.y));
		}
		return worldPoints;
	}
}
