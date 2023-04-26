#include "ExampleClass.h"

// .cpp file

ExampleClass::ExampleClass()
{
	// gets a random number between 0 and 2
	// collider type can be 0, 1 or 2
	int random = rand() % 3;

	switch (random)
	{
	case 0:
		collider = CollisionManager::RegisterNewCollider<ExampleClass, BoxCollider>(this, new BoxCollider(Vec2(xPOS, yPOS), Vec2(100, 100)));
		break;
	case 1:
		collider = CollisionManager::RegisterNewCollider<ExampleClass, CircleCollider>(this, new CircleCollider(Vec2(xPOS , yPOS), 50, 1));
		break;
	case 2:
		collider = CollisionManager::RegisterNewCollider<ExampleClass, PolygonCollider>(this, new PolygonCollider(Vec2(xPOS, yPOS), PolygonShape::GetRandomPolygon(50)));
		break;
	default:break;
	}

	// add a listener to the collider
	collider->AddListener(std::bind(&ExampleClass::OnCollisionEvent, this, std::placeholders::_1));
}

void ExampleClass::OnCollisionEvent(Collision collision)
{
	// get the owner of the collider that collided with this object
	ExampleClass* collideObject = collision.GetColliderHit()->GetOwnerAs<ExampleClass>();
}

void ExampleClass::Update(float deltaTime)
{
	// update the position of the collider
	collider->UpdatePosition(Vec2(xPOS, yPOS));
}
