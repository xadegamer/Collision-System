#pragma once

#include "Vec2.h"

#include "Collider.h"

namespace CollisionSystem
{
	template <class T>
	class Collision
	{
	private:

		Collider<T>* _colliderHit = nullptr;
		Vec2 _minimumTranslationVector = Vec2(0, 0);
		float _impulse = 0;

	public:

		Collision() = default;

		/// <summary>
		/// Constructor that initializes the properties of the collision.
		/// </summary>
		/// <param name="colliderHit">The collider that was hit.</param>
		/// <param name="minimumTranslationVector">The minimum translation vector required to separate the two colliders.</param>
		/// <param name="impulse">The impulse of the collision.</param>
		Collision(Collider<T>* colliderHit, Vec2 minimumTranslationVector, float impulse)
		{
			_colliderHit = colliderHit;
			_minimumTranslationVector = minimumTranslationVector;
			_impulse = impulse;
		}

		/// <summary>
		/// Getter function for the collider that was hit in the collision.
		/// </summary>
		/// <returns>The collider that was hit in the collision</returns>
		Collider<T>* GetColliderHit()
		{
			return _colliderHit; 
		}

		/// <summary>
		/// Getter function for the minimum translation vector for the collision.
		/// </summary>
		/// <returns>The minimum translation vector for the collision</returns>
		Vec2 GetMinimumTranslationVector() 
		{
			return _minimumTranslationVector; 
		}

		/// <summary>
		/// Getter function for the impulse for the collision.
		/// </summary>
		/// <returns>The impulse for the collision</returns>
		inline float GetImpulse() { return _impulse; }
	};
}
