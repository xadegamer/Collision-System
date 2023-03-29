#pragma once

#include "Character.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include <functional>

class Enemy : public Character
{
private:

	Vector2 spawnPoint;
	Vector2 currentPatrolPoint;
	Vector2 direction;

	GameObject* target;
	
public:

	Enemy(Vector2 position);
	~Enemy();

	void Update(float deltaTime) override;

	void OnCollisionEnter(Collider* other) override;

	void PatrolState(float deltaTime);
};

