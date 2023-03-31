#pragma once

#include "SDLManager.h"
#include "GameObject.h"
#include "AssetManager.h"
#include <stdio.h>
#include <functional>
#include <any>
#include <iostream>
#include <string>

class Collider
{	
protected:

	static std::vector<Collider*> allColliders;

	void* owner;

	Vector2 position;

	bool isEnabled;
	bool isTrigger;
	bool isStatic;
	Collider* currentCollidedObject;
	std::function <void(Collider* other)> OnCollisionEnterEvent;
	
public:
	
	inline std::function <void(Collider* other)>& GetOnCollisionEnterEvent() { return OnCollisionEnterEvent; }
	
	Collider();
	
	~Collider();

	virtual void SetUp(void* owner, Vector2 nextPosition, bool isStatic = false);

	virtual void UpdatePosition(Vector2 nextPosition) = 0;

	virtual void Draw() = 0;

	virtual Vector2 GetCentre() = 0;

	void OnCollision(Collider* other);

	inline Vector2 GetPosition() { return position; }

	inline void* GetOwner() { return owner; }
	
	inline bool IsTrigger() { return isTrigger; }
	
	inline void SetTrigger(bool isTrigger) { this->isTrigger = isTrigger; }

	inline bool IsStatic() { return isStatic; }
	
	inline void SetStatic(bool isStatic) { this->isStatic = isStatic; }

	inline bool GetIsEnabled() { return isEnabled; }

	inline void SetIsEnabled(bool isEnabled) { this->isEnabled = isEnabled; }

	inline static std::vector<Collider*> GetAllColliders() { return allColliders; }
};