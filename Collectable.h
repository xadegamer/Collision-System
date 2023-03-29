#pragma once

#include "Prop.h"

#include "Player.h"

class Collectable : public Prop
{
	
protected:
	float amount;
	
public:
	Collectable(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, float amount);
	~Collectable();

	void Update(float deltaTime) override;

	void OnCollisionEnter(Collider* other) override;
	virtual void PickUp(Player* player);
};