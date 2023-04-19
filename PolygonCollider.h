#pragma once

#include "Collider.h"
#include <iostream>
#include <vector>
#include "Vec2.h"

	template <class T>
	class PolygonCollider : public Collider<T>
	{
	private:
		std::vector<Vec2> _points;

	public:

		/// <summary>
		/// PolygonCollider class that represents a polygon collider
		/// </summary>
		/// <param name="owner">A pointer to the object that owns the collider</param>
		/// <param name="position">The initial position of the collider</param>
		/// <param name="points">A vector containing the points that define the polygon's shape</param>
		/// <param name="isStatic">A bool to determine if the collider is static or dynamic</param>
		PolygonCollider(T* owner, Vec2 position, std::vector<Vec2> points, bool isStatic = false);

		/// <summary>
		/// Updates the position of the collider
		/// </summary>
		/// <param name="nextPosition">The next position of the collider</param>
		void UpdatePosition(Vec2 nextPosition) override;

		/// <summary>
		/// Returns the center of the polygon collider
		/// </summary>
		/// <returns>A Vec2 that represents the center of the collider</returns>
		Vec2 GetCenter() override;

		/// <summary>
		/// Returns the number of points that define the polygon collider
		/// </summary>
		/// <returns>An int representing the number of points</returns>
		int GetNumPoints();

		/// <summary>
		/// Returns a vector containing the points that define the polygon's shape
		/// </summary>
		/// <returns>A vector of Vec2 representing the points</returns>
		std::vector<Vec2> GetPoints();

		/// <summary>
		/// Returns a vector containing the polygon's points in world space
		/// </summary>
		/// <returns>A vector of Vec2 representing the points in world space</returns>
		std::vector<Vec2> GetWorldPoints();
	};

	template<class T>
	PolygonCollider<T>::PolygonCollider(T* owner, Vec2 position, std::vector<Vec2> points, bool isStatic) : Collider<T>(owner, position, isStatic)
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
	int PolygonCollider<T>::GetNumPoints()
	{
		return _points.size();
	}

	template<class T>
	std::vector<Vec2> PolygonCollider<T>::GetPoints()
	{
		return _points;
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

