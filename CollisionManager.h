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
	
	static bool DoBoxToBoxCollisionCheck(SDL_Rect* A, SDL_Rect* B, int buffer);
	static bool DoCircleToCircleCollsionCheck(SDL_Rect* a,float radiousA, SDL_Rect* b, float radiousB);
	static bool DoBoxToCircleCollsionCheck(SDL_Rect* box, SDL_Rect* circle, float radious);	

	static bool DoPolygonToPolygonCollisionCheck(Polygon* A, Polygon* B, int buffer);

	static bool CheckCollision(Collider* colA, Collider* colB);

	static double DistanceSquared(int x1, int y1, int x2, int y2);
	
	static void HandleAllCollision();

	static void VisualiseCollision();
};

