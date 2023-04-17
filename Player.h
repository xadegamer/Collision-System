#pragma once
#include "GameObject.h"

#include "TimeManager.h"

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"

#include <iostream>

extern TimeManager systemTimer;

class Player : public GameObject
{
private:

	RigidBody* rigidBody = nullptr;

	Collider* collider = nullptr;

	float moveSpeed = 0;
	
	float runSpeed = 0;

	float currentMoveSpeed = 0;
	
public:

	Player(Vector2 position);
	
	void Update(float deltaTime) override;

	void LateUpdate(float deltaTime) override;
	
	void OnCollisionEnter(Collision collision) override;
};

