#pragma once

#include "Collider.h"
#include <iostream>
#include <vector>

class PolygonCollider : public Collider
{
private:

	Vec2 position;
    int num_points;
	std::vector<Vec2> points;

public:

	PolygonCollider(void* owner, Vec2 nextPosition, std::vector<Vec2> points, bool isStatic = false);

	void UpdatePosition(Vec2 nextPosition) override;

	Vec2 GetCenter() override;

	inline int GetNumPoints() { return num_points; }

	inline std::vector<Vec2> GetPoints() { return points; }

	std::vector<Vec2> GetWorldPoints();
};

