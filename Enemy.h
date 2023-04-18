#pragma once

#include "GameObject.h"

class Enemy : public GameObject
{
private:

	RigidBody* rigidBody = nullptr;
	Vector2 direction = Vector2(0, 0);
	float moveSpeed = 0;
	
public:

	Enemy(Vector2 position);

	void Update(float deltaTime) override;

	void LateUpdate(float deltaTime) override;

	void OnCollisionEnter(Collision<GameObject> collision) override;
};

