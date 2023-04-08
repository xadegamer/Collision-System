#include "Prop.h"

#include "PolygonShape.h"

Prop::Prop(Vector2 position, int sortingOrder, bool isStatic) : GameObject(position)
{
	// random collider type
	int random = rand() % 3;

	switch (random)
	{
	case 0:
		collider = new BoxCollider{ (GameObject*)this, transform->GetPosition(), Vector2(100, 100),isStatic };
		break;
	case 1:
		collider = new CircleCollider{ (GameObject*)this, transform->GetPosition(), 50 ,1, isStatic };
		break;
	case 2:
		collider = new PolygonCollider((GameObject*)this, transform->GetPosition(), PolygonShape::GetRandomPolygon(50), isStatic);
		break;
	default:break;
	}
}

Prop::~Prop()
{
	
}

void Prop::Update(float deltaTime)
{
	collider->UpdatePosition(transform->GetPosition());
	GameObject::Update(deltaTime);
}