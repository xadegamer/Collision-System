#pragma once

#include "Collider.h"

#include "Collision.h"

using namespace CollisionSystem;

class CollisionResolver
{
public:

	static void Initialize();

	static void ResolveCollision(Collider* A, Collider* B);
};

