#include "ExampleClass.h"

// .cpp file

ExampleClass::ExampleClass()
{
	// localPoints from pre defined shapes
	std::vector<Vec2> localPoints = PolygonShape::GetPolygon(PolygonShapeType::SQUARE, 10);

	// OR for custom shape you can use this localPoints =  { Vec2(0, 0), Vec2(10, 0), Vec2(10, 10), Vec2(0, 10) };

	// register the collider with the collision manager
	polygonCollider = CollisionManager::RegisterNewCollider<ExampleClass, PolygonCollider>(this, new PolygonCollider(Vec2(xPOS, yPOS), localPoints, true));

	// add a listener to the collider
	polygonCollider->AddListener(std::bind(&ExampleClass::OnCollisionEvent, this, std::placeholders::_1));
}

void ExampleClass::OnCollisionEvent(Collision collision)
{
	// get the owner of the collider that collided with this object
	ExampleClass* collideObject = collision.GetColliderHit()->GetOwnerAs<ExampleClass>();
}

void ExampleClass::Update(float deltaTime)
{
	// update the position of the collider
	polygonCollider->UpdatePosition(Vec2(xPOS, yPOS));
}
