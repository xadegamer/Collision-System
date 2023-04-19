#pragma once
#include "Collider.h"

namespace CollisionSystem
{
	template <class T>
	class CircleCollider : public Collider<T>
	{
	private:

		float _radius;

	public:

		/// <summary>
		/// Constructor for the CircleCollider class.
		/// </summary>
		/// <param name="owner">A void pointer to the owner of the collider</param>
		/// <param name="nextPosition">The next position of the collider</param>
		/// <param name="radius">The radius of the circle collider</param>
		/// <param name="radiousMutiplier">A multiplier for the radius of the circle collider</param>
		/// <param name="isStatic">A bool indicating if the collider is static or not</param>
		CircleCollider(T* owner, Vec2 nextPosition, float radius, float radiousMutiplier = 1, bool isStatic = false);

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
		float GetRadius();
	};
}

#include "CircleCollider.h"
