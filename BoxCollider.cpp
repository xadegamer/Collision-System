#include "BoxCollider.h"

BoxCollider::BoxCollider(void* owner, Vector2 nextPosition, Vector2 size, bool isStatic) : Collider(owner, nextPosition, isStatic)
{
	width = size.x;
	height = size.y;
	UpdatePosition(nextPosition);
}

void BoxCollider::UpdatePosition(Vector2 nextPosition)
{
	position = nextPosition;
}

Vector2 BoxCollider::GetCenter()
{
	return Vector2(position.x + width / 2, position.y + height / 2);
}

std::vector<Vector2> BoxCollider::GetWorldPoints()
{
	std::vector<Vector2> points;
	points.push_back(Vector2(position.x, position.y));
	points.push_back(Vector2(position.x + width, position.y));
	points.push_back(Vector2(position.x + width, position.y + height));
	points.push_back(Vector2(position.x, position.y + height));
    return points;
}