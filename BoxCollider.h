#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
private:

	int width;
	int height;

public:

	void SetUp(void* owner, Vector2 nextPosition, Vector2 size, bool isStatic = false);

	void UpdatePosition(Vector2 nextPosition) override;

	Vector2 GetCentre() override;

	inline int GetWidth() { return width; }

	inline int GetHeight() { return height; }

	std::vector<Vector2> GetWorldPoints();
};

