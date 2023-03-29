#pragma once
#include "Character.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

#include "TimeManager.h"

#include <iostream>

extern TimeManager systemTimer;

class Game;

class Player : public Character
{
private:
	
	float runSpeed;
	
public:

	Player(Vector2 position);
	~Player();
	
	void Update(float deltaTime) override;

	void LateUpdate(float deltaTime) override;
	
	void OnCollisionEnter(Collider* other) override;
};

