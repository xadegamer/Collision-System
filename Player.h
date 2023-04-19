#pragma once
#include "GameObject.h"

#include "TimeManager.h"

#include <iostream>

extern TimeManager systemTimer;

class Player : public GameObject
{
private:

	RigidBody* rigidBody = nullptr;
	float moveSpeed = 0;
	float runSpeed = 0;
	float currentMoveSpeed = 0;
	
public:

	Player(Vector2 position);
	
	void Update(float deltaTime) override;

	void LateUpdate(float deltaTime) override;
	
	void OnCollisionEnter(Collision<GameObject> collision) override;
};

