#pragma once

class Collider;

class Collision
{
private:

	Collider* colliderHit;
	Vector2 minimumTranslationVector;

	public:

		Collision() = default;

		Collision(Collider* colliderHit, Vector2 minimumTranslationVector)
		{
			this->colliderHit = colliderHit;
			this->minimumTranslationVector = minimumTranslationVector;
		}

		// setters
		inline void SetColliderHit(Collider* colliderHit) { this->colliderHit = colliderHit; }
		inline void SetMinimumTranslationVector(Vector2 minimumTranslationVector) { this->minimumTranslationVector = minimumTranslationVector; }

		// getters
		inline Collider* GetColliderHit() { return colliderHit; }
		inline Vector2 GetMinimumTranslationVector() { return minimumTranslationVector; }
};

