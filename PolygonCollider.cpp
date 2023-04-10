#include "PolygonCollider.h"

namespace CollisionSystem
{
	PolygonCollider::PolygonCollider(void* owner, Vec2 position, std::vector<Vec2> points, bool isStatic) : Collider(owner, position, isStatic)
	{
		_points = points;
		_num_points = _points.size();
		UpdatePosition(position);
	}

	void PolygonCollider::UpdatePosition(Vec2 nextPosition)
	{
		_position = nextPosition;
	}

	Vec2 PolygonCollider::GetCenter()
	{
		Vec2 center = Vec2(0, 0);
		for (int i = 0; i < _num_points; i++)
		{
			center += _points[i];
		}
		center /= _num_points;
		return center + _position;
	}

	std::vector<Vec2> PolygonCollider::GetWorldPoints()
	{
		std::vector<Vec2> worldPoints;
		for (int i = 0; i < _num_points; i++)
		{
			worldPoints.push_back(Vec2(_points[i].GetX() + _position.GetX(), _points[i].GetY() + _position.GetY()));
		}
		return worldPoints;
	}
}
