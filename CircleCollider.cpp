#include "CircleCollider.h"

namespace CollisionSystem
{
	template<class T>
	CircleCollider<T>::CircleCollider(T* owner, Vec2 nextPosition, float radius, float radiousMutiplier, bool isStatic) : Collider(owner, nextPosition, isStatic)
	{
		_radius = radius * radiousMutiplier;
		UpdatePosition(position);
	}

	template<class T>
	void CircleCollider<T>::UpdatePosition(Vec2 nextPosition)
	{
		Vec2 currentPosition = Vec2(nextPosition.GetX() + _radius, nextPosition.GetY() + _radius);
		_position = currentPosition;
	}

	template<class T>
	Vec2 CircleCollider<T>::GetCenter()
	{
		return _position;
	}
}
