#include "PolygonCollider.h"

namespace CollisionSystem
{
	PolygonCollider::PolygonCollider(Vec2 position, std::vector<Vec2> points, bool isStatic) : Collider(position, isStatic)
	{
		_points = points;
		UpdatePosition(position);
	}

	void PolygonCollider::UpdatePosition(Vec2 nextPosition)
	{
		_position = nextPosition;
	}

	Vec2 PolygonCollider::GetCenter()
	{
		Vec2 center = Vec2(0, 0);
		for (int i = 0; i < GetNumPoints(); i++)
		{
			center += _points[i];
		}
		center /= GetNumPoints();
		return center + _position;
	}

	std::vector<Vec2> PolygonCollider::GetWorldPoints()
	{
		std::vector<Vec2> worldPoints;
		for (int i = 0; i < GetNumPoints(); i++)
		{
			worldPoints.push_back(Vec2(_points[i].GetX() + _position.GetX(), _points[i].GetY() + _position.GetY()));
		}
		return worldPoints;
	}
}
