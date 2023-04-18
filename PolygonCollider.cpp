#include "PolygonCollider.h"

namespace CollisionSystem
{
	template<class T>
	PolygonCollider<T>::PolygonCollider(T* owner, Vec2 position, std::vector<Vec2> points, bool isStatic) : Collider(owner, position, isStatic)
	{
		_points = points;
		UpdatePosition(position);
	}

	template<class T>
	void PolygonCollider<T>::UpdatePosition(Vec2 nextPosition)
	{
		_position = nextPosition;
	}

	template<class T>
	Vec2 PolygonCollider<T>::GetCenter()
	{
		Vec2 center = Vec2(0, 0);
		for (int i = 0; i < GetNumPoints(); i++)
		{
			center += _points[i];
		}
		center /= GetNumPoints();
		return center + _position;
	}

	template<class T>
	std::vector<Vec2> PolygonCollider<T>::GetWorldPoints()
	{
		std::vector<Vec2> worldPoints;
		for (int i = 0; i < GetNumPoints(); i++)
		{
			worldPoints.push_back(Vec2(_points[i].GetX() + _position.GetX(), _points[i].GetY() + _position.GetY()));
		}
		return worldPoints;
	}
}
