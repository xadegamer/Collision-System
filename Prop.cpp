#include "Prop.h"

#include "PolygonShape.h"

Prop::Prop(Vector2 position, int sortingOrder, bool isStatic) : GameObject(position)
{
	// random collider type
	int random = rand() % 3;

	switch (random)
	{
	case 0:
		collider = new BoxCollider(Vec2(transform->GetPosition().x, transform->GetPosition().y), Vec2(100, 100),isStatic );
		break;
	case 1:
		collider = new CircleCollider(Vec2(transform->GetPosition().x, transform->GetPosition().y), 50,1,isStatic );
		break;
	case 2:
		collider = new PolygonCollider(Vec2(transform->GetPosition().x, transform->GetPosition().y), PolygonShape::GetRandomPolygon(50), isStatic);
		break;
	default:break;
	}

	collider->AddOwnerAs<GameObject>(this);
}

Prop::~Prop()
{
	
}

void Prop::Update(float deltaTime)
{
	collider->UpdatePosition(Vec2(transform->GetPosition().x, transform->GetPosition().y));
	GameObject::Update(deltaTime);
}