#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
private:
	float radius;
	
public:

	void SetUp(Transform* owner, Vector2 size, float radiousMutiplier = 1, bool isStatic = false);
	void Update() override;
	void Draw() override;
	inline float GetRadius() { return radius; };
};

