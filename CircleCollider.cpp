#include "CircleCollider.h"

namespace CollisionSystem
{
	void CircleCollider::UpdatePosition(Vec2 nextPosition)
	{
		Vec2 currentPosition = Vec2(nextPosition.GetX() + _radius, nextPosition.GetY() + _radius);
		_position = currentPosition;
	}

	Vec2 CircleCollider::GetCenter()
	{
		return _position;
	}
}
