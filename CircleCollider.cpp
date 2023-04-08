#include "CircleCollider.h"

CircleCollider::CircleCollider(void* owner, Vector2 nextPosition, float _radius, float radiousMutiplier, bool isStatic) : Collider(owner, nextPosition, isStatic)
{
	radius = _radius * radiousMutiplier;
	UpdatePosition(nextPosition);
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
