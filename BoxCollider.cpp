#include "BoxCollider.h"

namespace CollisionSystem
{
	BoxCollider::BoxCollider(void* owner, Vec2 nextPosition, Vec2 size, bool isStatic) : Collider(owner, nextPosition, isStatic)
	{
		width = size.GetX();
		height = size.GetY();
		UpdatePosition(nextPosition);
	}

	void BoxCollider::UpdatePosition(Vec2 nextPosition)
	{
		position = nextPosition;
	}

	Vec2 BoxCollider::GetCenter()
	{
		return Vec2(position.GetX() + width / 2, position.GetY() + height / 2);
	}

	std::vector<Vec2> BoxCollider::GetWorldPoints()
	{
		std::vector<Vec2> points;
		points.push_back(Vec2(position.GetX(), position.GetY()));
		points.push_back(Vec2(position.GetX() + width, position.GetY()));
		points.push_back(Vec2(position.GetX() + width, position.GetY() + height));
		points.push_back(Vec2(position.GetX(), position.GetY() + height));
		return points;
	}
}
