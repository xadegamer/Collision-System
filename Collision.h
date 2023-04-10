#pragma once

#include "Vec2.h"

namespace CollisionSystem
{
	class Collider;

	class Collision
	{
	private:

		Collider* _colliderHit = nullptr;
		Vec2 _minimumTranslationVector = Vec2(0, 0);
		float _impulse = 0;

	public:

		Collision() = default;

		Collision(Collider* colliderHit, Vec2 minimumTranslationVector, float impulse) : _colliderHit(colliderHit), _minimumTranslationVector(minimumTranslationVector), _impulse(impulse)
		{

		}

		inline Collider* GetColliderHit() { return _colliderHit; }
		inline Vec2 GetMinimumTranslationVector() { return _minimumTranslationVector; }
		inline float GetImpulse() { return _impulse; }
	};
}
