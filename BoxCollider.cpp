#include "BoxCollider.h"

namespace CollisionSystem
{
	template<class T>
	BoxCollider<T>::BoxCollider(T* owner, Vec2 nextPosition, Vec2 size, bool isStatic) : Collider<T>(owner, nextPosition, isStatic)
	{
		_size = size;
		UpdatePosition(nextPosition);
	}

	template<class T>
	void BoxCollider<T>::UpdatePosition(Vec2 nextPosition)
	{
		_position = nextPosition;
	}

	template<class T>
	Vec2 BoxCollider<T>::GetCenter()
	{
		return Vec2(_position.GetX() + GetWidth() / 2, _position.GetY() + GetHeight() / 2);
	}

	template<class T>
	std::vector<Vec2> BoxCollider<T>::GetWorldPoints()
	{
		std::vector<Vec2> points;
		points.push_back(Vec2(_position.GetX(), _position.GetY()));
		points.push_back(Vec2(_position.GetX() + GetWidth(), _position.GetY()));
		points.push_back(Vec2(_position.GetX() + GetWidth(), _position.GetY() + GetHeight()));
		points.push_back(Vec2(_position.GetX(), _position.GetY() + GetHeight()));
		return points;
	}
}
