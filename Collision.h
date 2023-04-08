#pragma once

#include "Vector2.h"

class Collider;

class Collision
{
private:

	Collider* colliderHit;
	Vector2 minimumTranslationVector;
	float impulse;

	public:

		Collision() = default;

		Collision(Collider* colliderHit, Vector2 minimumTranslationVector, float impulse)
		{
			this->colliderHit = colliderHit;
			this->minimumTranslationVector = minimumTranslationVector;
			this->impulse = impulse;
		}

		// setters
		inline void SetColliderHit(Collider* colliderHit) { this->colliderHit = colliderHit; }
		inline void SetMinimumTranslationVector(Vector2 minimumTranslationVector) { this->minimumTranslationVector = minimumTranslationVector; }
		inline void SetImpulse(float impulse) { this->impulse = impulse; }

		// getters
		inline Collider* GetColliderHit() { return colliderHit; }
		inline Vector2 GetMinimumTranslationVector() { return minimumTranslationVector; }
		inline float GetImpulse() { return impulse; }
};

