#pragma once

#include "Collider.h"
#include <iostream>
#include <vector>

struct Polygon 
{
	Vector2 position; // Position of polygon
    int num_points; // Number of points in polygon
    SDL_Point* points; // Array of points
    SDL_Color color; // Color
};

class PolygonCollider : public Collider
{
private:

	Polygon* polygon;
public:
	void SetUp(Transform* owner, SDL_Point* points, float sizeMutiplier = 1, bool isStatic = false);
	void Update() override;
	void Draw() override;
};

