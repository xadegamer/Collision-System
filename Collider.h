#pragma once

#include "SDLManager.h"
#include "GameObject.h"
#include "AssetManager.h"
#include <stdio.h>
#include <functional>

class Collider : public Component
{
	
protected:
	
	Transform* owner;
	Vector2 offset;
	bool isTrigger;
	bool isStatic;
	Collider* currentCollidedObject;
	SDL_Rect* colliderRect;
	std::function <void(Collider* other)> OnCollisionEnterEvent;
	
public:
	
	inline std::function <void(Collider* other)>& GetOnCollisionEnterEvent() { return OnCollisionEnterEvent; }
	
	Collider();
	
	~Collider();
	
	void someFunc();

	virtual void SetUp(Transform* owner, Vector2 size, bool isStatic = false);

	virtual void Update() {};

	virtual void Draw() {};

	void OnCollision(Collider* other);

	inline Vector2 GetPosition() { return Vector2(colliderRect->x, colliderRect->y); }

	inline Transform* GetOwner() { return owner; }
	
	inline bool IsTrigger() { return isTrigger; }
	
	inline void SetTrigger(bool isTrigger) { this->isTrigger = isTrigger; }

	inline bool IsStatic() { return isStatic; }
	
	inline void SetStatic(bool isStatic) { this->isStatic = isStatic; }

	Vector2 GetCentre();

	virtual SDL_Rect* GetColliderRect() { return colliderRect; };
};