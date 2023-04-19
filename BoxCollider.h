#pragma once
#include "Collider.h"

namespace CollisionSystem
{
	class BoxCollider : public Collider
	{
	private:

		Vec2 _size; // The size of the collider in the x and y dimensions.

	public:

		/// <summary>
		/// Constructor for creating a BoxCollider.
		/// </summary>
		/// <param name="owner">The owner of the collider</param>
		/// <param name="nextPosition">The position of the collider</param>
		/// <param name="size">The size of the box</param>
		/// <param name="isStatic">Whether the collider is static or not (default is false)</param>
		BoxCollider(Vec2 nextPosition, Vec2 size, bool isStatic = false);

		/// <summary>
		/// Updates the position of the collider to the given position.
		/// </summary>
		/// <param name="nextPosition">The position to update to</param>
		void UpdatePosition(Vec2 nextPosition) override;

		/// <summary>
		/// Gets the center point of the collider.
		/// </summary>
		/// <returns>The center point of the collider</returns>
		Vec2 GetCenter() override;

		/// <summary>
		/// Gets the width of the collider.
		/// </summary>
		/// <returns>The width of the collider</returns>
		inline float GetWidth() { return _size.GetX(); }

		/// <summary>
		/// Gets the height of the collider.
		/// </summary>
		/// <returns>The height of the collider</returns>
		inline float GetHeight() { return _size.GetY(); }

		/// <summary>
		/// Gets the number of points that define the collider's shape in world space.
		/// </summary>
		/// <returns>The number of points that define the collider's shape in world space</returns>
		inline int GetNumPoints() { return GetWorldPoints().size(); }

		/// <summary>
		/// Gets a vector of the points that define the collider's shape in world space.
		/// </summary>
		/// <returns>A vector of the points that define the collider's shape in world space</returns>
		std::vector<Vec2> GetWorldPoints();
	};
}
