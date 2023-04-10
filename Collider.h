#pragma once

#include <stdio.h>
#include <functional>
#include <iostream>
#include <string>

#include "Collision.h"
#include "Vec2.h"

class Collider
{	
protected:

	static std::vector<Collider*> allColliders;
	Collision collision;
	void* owner;
	float xPos;
	float yPos;
	Vec2 position;
	bool isEnabled;
	bool isTrigger;
	bool isStatic;
	Collider* currentCollidedObject;
	std::function <void(Collision other)> OnCollisionEnterEvent;
	
public:
	
	Collider(void* owner, Vec2 position, bool isStatic = false);
	
	~Collider();

	virtual void UpdatePosition(Vec2 position) = 0;

	virtual Vec2 GetCenter() = 0;

	void OnCollision();

	void SetCollisionProperty(Collider* colliderHit, Vec2 minimumTranslationVector, float impulse);

	void AddListener(std::function <void(Collision other)> OnCollisionEnterEvent);

	inline Collision GetCollision() { return collision; }

	inline Vec2 GetPosition() { return position; }

	inline void* GetOwner() { return owner; }
	
	inline bool IsTrigger() { return isTrigger; }
	
	inline void SetTrigger(bool isTrigger) { this->isTrigger = isTrigger; }

	inline bool IsStatic() { return isStatic; }
	
	inline void SetStatic(bool isStatic) { this->isStatic = isStatic; }

	inline bool GetIsEnabled() { return isEnabled; }

	inline void SetIsEnabled(bool isEnabled) { this->isEnabled = isEnabled; }

	inline static std::vector<Collider*> GetAllColliders() { return allColliders; }
};