#include "BoxCollider.h"

namespace CollisionSystem
{
	BoxCollider::BoxCollider(void* owner, Vec2 nextPosition, Vec2 size, bool isStatic) : Collider(owner, nextPosition, isStatic)
	{
		width = size.x;
		height = size.y;
		UpdatePosition(nextPosition);
	}

	void BoxCollider::UpdatePosition(Vec2 nextPosition)
	{
		position = nextPosition;
	}

	Vec2 BoxCollider::GetCenter()
	{
		return Vec2(position.x + width / 2, position.y + height / 2);
	}

	std::vector<Vec2> BoxCollider::GetWorldPoints()
	{
		std::vector<Vec2> points;
		points.push_back(Vec2(position.x, position.y));
		points.push_back(Vec2(position.x + width, position.y));
		points.push_back(Vec2(position.x + width, position.y + height));
		points.push_back(Vec2(position.x, position.y + height));
		return points;
	}
}
