#pragma once

#include "GameObject.h"

#include "BoxCollider.h"

#include "CircleCollider.h"

#include "PolygonCollider.h"

#include <functional>

class Enemy : public GameObject
{
private:

	RigidBody* rigidBody = nullptr;

	Collider* collider = nullptr;

	Vector2 direction = Vector2(0, 0);

	GameObject* target = nullptr;

	float moveSpeed = 0;
	
public:

	Enemy(Vector2 position);

	void Update(float deltaTime) override;

	void LateUpdate(float deltaTime) override;

	void OnCollisionEnter(Collision collision) override;
};

