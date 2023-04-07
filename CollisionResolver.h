#pragma once

#include "Collider.h"

#include "Collision.h"

class CollisionResolver
{
public:

	static void Initialize();

	static void Shutdown();

	static void ResolveCollision(std::vector<Collision> collisions);
};

