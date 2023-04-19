#include "BoxCollider.h"

namespace CollisionSystem
{
	void BoxCollider::UpdatePosition(Vec2 nextPosition)
	{
		_position = nextPosition;
	}

	Vec2 BoxCollider::GetCenter()
	{
		return Vec2(_position.GetX() + GetWidth() / 2, _position.GetY() + GetHeight() / 2);
	}

	std::vector<Vec2> BoxCollider::GetWorldPoints()
	{
		std::vector<Vec2> points;
		points.push_back(Vec2(_position.GetX(), _position.GetY()));
		points.push_back(Vec2(_position.GetX() + GetWidth(), _position.GetY()));
		points.push_back(Vec2(_position.GetX() + GetWidth(), _position.GetY() + GetHeight()));
		points.push_back(Vec2(_position.GetX(), _position.GetY() + GetHeight()));
		return points;
	}
}
