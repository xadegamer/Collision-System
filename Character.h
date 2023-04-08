#pragma once
#include "GameObject.h"

#include "CircleCollider.h"

#include "TimeManager.h"

#include <iostream>

class Character : public GameObject
{
protected:
;
	RigidBody* rigidBody;

	float moveSpeed;

	float currentMoveSpeed;
	
	bool canMove = true;
	
public:

	Character(Vector2 position);

	~Character();

	virtual void Update(float deltaTime) override;
};