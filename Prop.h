#pragma once
#include "GameObject.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"

class Prop : public GameObject
{
protected:

	RigidBody* rigidBody;

	Collider* collider;
	
public:

	Prop(Vector2 position, int sortingOrder, bool isStatic);

	~Prop();

	void Update(float deltaTime) override;
};

