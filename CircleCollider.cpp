#include "CircleCollider.h"

namespace CollisionSystem
{
	CircleCollider::CircleCollider(Vec2 nextPosition, float radius, float radiousMutiplier, bool isStatic) : Collider(nextPosition, isStatic)
	{
		_radius = radius * radiousMutiplier;
		UpdatePosition(nextPosition);
	}

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
