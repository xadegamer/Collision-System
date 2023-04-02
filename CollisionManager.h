#pragma once

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"

class CollisionManager
{
private:
	CollisionManager() = delete;
	~CollisionManager() = delete;
	
public:

	static void HandleAllCollision();

	static bool CheckCollision(Collider* colA, Collider* colB);

	static bool BoxToBoxCollisionCheck(BoxCollider* A, BoxCollider* B, int buffer);

	static bool CircleToCircleCollsionCheck (CircleCollider* A, CircleCollider* B, int buffer);

	static bool BoxToCircleCollsionCheck(BoxCollider* box, CircleCollider* circle, int buffer);

	static bool PolygonToPolygonCollisionCheck (PolygonCollider* A, PolygonCollider* B, int buffer);

	static bool PolygonToCircleCollisionCheck(PolygonCollider* poly, CircleCollider* circle, int buffer);

	static bool PolygonToBoxCollisionCheck(PolygonCollider* poly, BoxCollider* box, int buffer);

	static double DistanceSquared(int x1, int y1, int x2, int y2);

	static bool PolygonContainsPoint(const std::vector<Vector2>& polyPoints, const Vector2& point);
};

