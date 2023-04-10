#pragma once

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"

#include <stdio.h>
#include <functional>


class CollisionManager
{
public:
	static std::function <void(Collider* colA, Collider* colB)> OnAnyCollisionEvent;

private:
	CollisionManager() = delete;
	~CollisionManager() = delete;

	static bool CheckCollision(Collider* colA, Collider* colB);

	static bool BoxToBoxCollisionCheck(BoxCollider* boxA, BoxCollider* boxB, int buffer);

	static bool CircleToCircleCollsionCheck(CircleCollider* circleA, CircleCollider* circleB, int buffer);

	static bool BoxToCircleCollsionCheck(BoxCollider* box, CircleCollider* circle, int buffer);

	static bool PolygonToPolygonCollisionCheck(PolygonCollider* polyA, PolygonCollider* polyB, int buffer);

	static bool PolygonToCircleCollisionCheck(PolygonCollider* poly, CircleCollider* circle, int buffer);

	static bool PolygonToBoxCollisionCheck(PolygonCollider* poly, BoxCollider* box, int buffer);

	static bool SATPolyToPolyCalculation(std::vector<Vec2> A, std::vector<Vec2> B, int buffer, Vec2* mtv);

	static bool SATPolyToCircleCalculation(std::vector<Vec2> polyPoints, Vec2 circlePos, float circleRadious, int buffer, Vec2* mtv);

	static double DistanceSquared(int x1, int y1, int x2, int y2);

	static bool PolygonContainsPoint(const std::vector<Vec2>& polyPoints, const Vec2& point);
	
public:

	static void AddListener(std::function <void(Collider* colA, Collider* colB)> func);

	static void HandleAllCollision();

	static void CleanUp();
};

