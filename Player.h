#pragma once
#include "Character.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"

#include "TimeManager.h"

#include <iostream>

extern TimeManager systemTimer;

class Game;

class Player : public Character
{
private:

	Collider* collider;
	
	float runSpeed;
	
public:

	Player(Vector2 position);
	~Player();
	
	void Update(float deltaTime) override;

	void LateUpdate(float deltaTime) override;
	
	void OnCollisionEnter(Collision collision) override;
};

