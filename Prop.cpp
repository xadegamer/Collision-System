#include "Prop.h"

#include "PolygonShape.h"

Prop::Prop(Vector2 position, int sortingOrder, bool isStatic) : GameObject(position)
{
	// random collider type
	int random = rand() % 3;

	switch (random)
	{
	case 0:
		collider = new BoxCollider{ (GameObject*)this, Vec2(transform->GetPosition().x, transform->GetPosition().y), Vec2(100, 100) };
		break;
	case 1:
		collider = new CircleCollider{ (GameObject*)this, Vec2(transform->GetPosition().x, transform->GetPosition().y), 50 };
		break;
	case 2:
		collider = new PolygonCollider((GameObject*)this, Vec2(transform->GetPosition().x, transform->GetPosition().y), PolygonShape::GetRandomPolygon(50));
		break;
	default:break;
	}
}

Prop::~Prop()
{
	
}

void Prop::Update(float deltaTime)
{
	collider->UpdatePosition(Vec2(transform->GetPosition().x, transform->GetPosition().y));
	GameObject::Update(deltaTime);
}