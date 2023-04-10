#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
private:

	float radius;
	
public:

	CircleCollider(void* owner, Vector2 nextPosition, float radius, float radiousMutiplier = 1, bool isStatic = false);

	void UpdatePosition(Vector2 nextPosition) override;

	Vector2 GetCenter() override;

	inline float GetRadius() { return radius; };
};

