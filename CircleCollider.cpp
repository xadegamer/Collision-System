#include "CircleCollider.h"

namespace CollisionSystem
{
	CircleCollider::CircleCollider(void* owner, Vec2 nextPosition, float _radius, float radiousMutiplier, bool isStatic) : Collider(owner, nextPosition, isStatic)
	{
		radius = _radius * radiousMutiplier;
		UpdatePosition(nextPosition);
	}

	void CircleCollider::UpdatePosition(Vec2 nextPosition)
	{
		Vec2 currentPosition = Vec2(nextPosition.GetX() + radius, nextPosition.GetY() + radius);
		position = currentPosition;
	}

	Vec2 CircleCollider::GetCenter()
	{
		return position;
	}
}
