#pragma once
#include "Collider.h"

namespace CollisionSystem
{
	class CircleCollider : public Collider
	{
	private:

		float _radius; // The radius of the circle collider.

	public:

		/// <summary>
		/// Constructor for the CircleCollider class.
		/// </summary>
		/// <param name="owner">A void pointer to the owner of the collider</param>
		/// <param name="nextPosition">The next position of the collider</param>
		/// <param name="radius">The radius of the circle collider</param>
		/// <param name="radiousMutiplier">A multiplier for the radius of the circle collider</param>
		/// <param name="isStatic">A bool indicating if the collider is static or not</param>
		CircleCollider(Vec2 nextPosition, float radius, float radiousMutiplier = 1, bool isStatic = false);

		/// <summary>
		/// Update the position of the circle collider.
		/// </summary>
		/// <param name="nextPosition">The next position of the circle collider</param>
		void UpdatePosition(Vec2 nextPosition) override;

		/// <summary>
		/// Getter function for the center position of the circle collider.
		/// </summary>
		/// <returns>The center position of the circle collider</returns>
		Vec2 GetCenter() override;

		/// <summary>
		/// Getter function for the radius of the circle collider.
		/// </summary>
		/// <returns>The radius of the circle collider</returns>
		inline float GetRadius() { return _radius; };
	};
}
