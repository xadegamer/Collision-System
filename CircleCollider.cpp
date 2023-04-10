#include "CircleCollider.h"

namespace CollisionSystem
{
	CircleCollider::CircleCollider(void* owner, Vec2 position, float radius, float radiousMutiplier, bool isStatic) : Collider(owner, position, isStatic)
	{
		_radius = radius * radiousMutiplier;
		UpdatePosition(position);
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
