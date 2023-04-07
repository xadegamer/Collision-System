#include "CircleCollider.h"

void CircleCollider::SetUp(void* owner, Vector2 nextPosition, float _radius, float radiousMutiplier , bool isStatic)
{
	Collider::SetUp(owner, nextPosition, isStatic);
	radius = _radius * radiousMutiplier;
}

void CircleCollider::UpdatePosition(Vector2 nextPosition)
{
	Vector2 currentPosition = Vector2(nextPosition.x + radius, nextPosition.y + radius);
	position = currentPosition;
}

Vector2 CircleCollider::GetCenter()
{
	return position;
}
