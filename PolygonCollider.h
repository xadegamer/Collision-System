#pragma once

#include "Collider.h"
#include <iostream>
#include <vector>

class PolygonCollider : public Collider
{
private:

	Vector2 position;
    int num_points;
	std::vector<Vector2> points;

public:

	PolygonCollider(void* owner, Vector2 nextPosition, std::vector<Vector2> points, bool isStatic = false);

	void UpdatePosition(Vector2 nextPosition) override;

	Vector2 GetCenter() override;

	inline int GetNumPoints() { return num_points; }

	inline std::vector<Vector2> GetPoints() { return points; }

	std::vector<Vector2> GetWorldPoints();
};

