#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
private:
	float radius;
	
public:

	void SetUp(void* owner, Vector2 nextPosition, float radius, float radiousMutiplier = 1, bool isStatic = false);
	void UpdatePosition(Vector2 nextPosition) override;

	void Draw() override;

	inline float GetRadius() { return radius; };
	Vector2 GetCentre() override;
};

