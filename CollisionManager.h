#pragma once

#include "SDLManager.h"

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"

class CollisionManager
{
private:
	CollisionManager() = delete;
	~CollisionManager() = delete;
	
public:

	static bool BoxToBoxCollisionCheck(BoxCollider* A, BoxCollider* B, int buffer);

	static bool CircleToCircleCollsionCheck (CircleCollider* A, CircleCollider* B, int buffer);

	static bool BoxToCircleCollsionCheck(BoxCollider* box, CircleCollider* circle, int buffer);

	static bool DoPolygonToPolygonCollisionCheck(Polygon* A, Polygon* B, int buffer);

	static bool CheckCollision(Collider* colA, Collider* colB);

	static double DistanceSquared(int x1, int y1, int x2, int y2);
	
	static void HandleAllCollision();

	static void VisualiseCollision();
};

