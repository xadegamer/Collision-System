#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
private:
	
	SDL_Rect* boxColliderRect;
	
public:
	void SetUp(Transform* owner, Vector2 size, float sizeMutiplier = 1 , bool isStatic = false);
	void Update() override;
	void Draw() override;
	SDL_Rect* GetColliderRect() override { return boxColliderRect; };
};

