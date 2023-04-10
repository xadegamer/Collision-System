#pragma once

#include "Vec2.h"

namespace CollisionSystem
{
	class Collider;

	class Collision
	{
	private:

		Collider* colliderHit = nullptr;
		Vec2 minimumTranslationVector = Vec2(0, 0);
		float impulse = 0;

	public:

		Collision() = default;

		Collision(Collider* colliderHit, Vec2 minimumTranslationVector, float impulse) : colliderHit(colliderHit), minimumTranslationVector(minimumTranslationVector), impulse(impulse)
		{

		}

		inline Collider* GetColliderHit() { return colliderHit; }
		inline Vec2 GetMinimumTranslationVector() { return minimumTranslationVector; }
		inline float GetImpulse() { return impulse; }
	};
}
