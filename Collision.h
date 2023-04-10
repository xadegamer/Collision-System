#pragma once

#include "Vector2.h"

class Collider;

class Collision
{
private:

	Collider* colliderHit = nullptr;
	Vector2 minimumTranslationVector = Vector2(0,0);
	float impulse = 0 ;

public:

	Collision() = default;

	Collision(Collider* colliderHit, Vector2 minimumTranslationVector, float impulse) : colliderHit(colliderHit), minimumTranslationVector(minimumTranslationVector), impulse(impulse) 
	{

	}

	inline Collider* GetColliderHit() { return colliderHit; }
	inline Vector2 GetMinimumTranslationVector() { return minimumTranslationVector; }
	inline float GetImpulse() { return impulse; }
};

