#pragma once

#include "GameObject.h"

class CollisionResolver
{
public:

	static void Initialize();

	/// <summary>
	/// Resolves a collision between two colliders by calculating and applying a minimum translation vector (MTV) to separate them
	/// </summary>
	/// <param name="A">The first collider involved in the collision</param>
	/// <param name="B">The second collider involved in the collision</param>
	static void ResolveCollision(Collider<GameObject>* A, Collider<GameObject>* B);
};