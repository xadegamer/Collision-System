#pragma once

#include "Collider.h"
#include <iostream>
#include <vector>

namespace CollisionSystem
{
	template<class T>
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
		inline int GetNumPoints() { return  _points.size(); }

		/// <summary>
		/// Returns a vector containing the points that define the polygon's shape
		/// </summary>
		/// <returns>A vector of Vec2 representing the points</returns>
		inline std::vector<Vec2> GetPoints() { return _points; }

		/// <summary>
		/// Returns a vector containing the polygon's points in world space
		/// </summary>
		/// <returns>A vector of Vec2 representing the points in world space</returns>
		std::vector<Vec2> GetWorldPoints();
	};
}

