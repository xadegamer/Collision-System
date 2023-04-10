#pragma once

#include "Collider.h"

#include "Collision.h"

class CollisionResolver
{
public:

	static void Initialize();

	static void ResolveCollision(Collider* A, Collider* B);
};

