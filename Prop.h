#pragma once
#include "GameObject.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PolygonCollider.h"

enum class ColliderType {BOX,CIRCLE, POLYGON};

class Prop : public GameObject
{
protected:
	ColliderType colliderType;
	SpriteRenderer* spriteRenderer;
	RigidBody* rigidBody;
	Collider* collider;
	
public:
	Prop(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, bool isStatic, bool isTrigger);
	~Prop();

	void Update(float deltaTime) override;
	void Draw() override;
};

