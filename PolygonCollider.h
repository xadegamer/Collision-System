#pragma once

#include "Collider.h"
#include <iostream>
#include <vector>

class PolygonCollider : public Collider
{
private:

	Vector2 position;
    int num_points; // Number of points in polygon
	std::vector<Vector2> points;

public:
	void SetUp(void* owner, Vector2 nextPosition, std::vector<Vector2> points, bool isStatic = false);
	void UpdatePosition(Vector2 nextPosition) override;

	void Draw() override;


	Vector2 GetCentre() override;

	inline int GetNumPoints() { return num_points; }
	inline std::vector<Vector2> GetPoints() { return points; }

	std::vector<Vector2> GetWorldPoints();

	void DrawCircleAtPosition(SDL_Color sdlColor, Vector2 position, int radius);
};

