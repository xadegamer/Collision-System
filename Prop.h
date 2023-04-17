#pragma once
#include "GameObject.h"

class Prop : public GameObject
{
protected:

	RigidBody* rigidBody;
	
public:

	Prop(Vector2 position, int sortingOrder, bool isStatic);

	~Prop();

	void Update(float deltaTime) override;
};

