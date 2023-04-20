#pragma once
// .h file

#include <vector>

#include "CollisionManager.h"

using namespace CollisionSystem;

class ExampleClass
{
private:

	float xPOS = 0;
	float yPOS = 0;

	PolygonCollider* polygonCollider = nullptr;

public:

	ExampleClass();
	void OnCollisionEvent(Collision collision);
	void Update(float deltaTime);
};

