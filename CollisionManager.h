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

	static std::vector<Collision> CheckCollision(Collider* colA, Collider* colB);

	static std::vector<Collision> BoxToBoxCollisionCheck(BoxCollider* A, BoxCollider* B, int buffer);

	static std::vector<Collision> CircleToCircleCollsionCheck (CircleCollider* A, CircleCollider* B, int buffer);

	static std::vector<Collision> BoxToCircleCollsionCheck(BoxCollider* box, CircleCollider* circle, int buffer);

	static std::vector<Collision> PolygonToPolygonCollisionCheck (PolygonCollider* A, PolygonCollider* B, int buffer);

	static std::vector<Collision> PolygonToCircleCollisionCheck(PolygonCollider* poly, CircleCollider* circle, int buffer);

	static std::vector<Collision> PolygonToBoxCollisionCheck(PolygonCollider* poly, BoxCollider* box, int buffer);

	static double DistanceSquared(int x1, int y1, int x2, int y2);

	static bool PolygonContainsPoint(const std::vector<Vector2>& polyPoints, const Vector2& point);
};

