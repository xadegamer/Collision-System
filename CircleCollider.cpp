#include "CircleCollider.h"

CircleCollider::CircleCollider(void* owner, Vec2 nextPosition, float _radius, float radiousMutiplier, bool isStatic) : Collider(owner, nextPosition, isStatic)
{
	radius = _radius * radiousMutiplier;
	UpdatePosition(nextPosition);
}

void CircleCollider::UpdatePosition(Vec2 nextPosition)
{
	Vec2 currentPosition = Vec2(nextPosition.x + radius, nextPosition.y + radius);
	position = currentPosition;
}

Vec2 CircleCollider::GetCenter()
{
	return position;
}
