#include "Rigidbody.h"

#define GRAVITY 9.8f

RigidBody::RigidBody()
{
	gravity = GRAVITY;
	mass = 1.0f;
}

RigidBody::~RigidBody()
{
	
}

void RigidBody::MoveToPosition(Vector2 position, float speed, float deltaTime)
{
	// move to new position with velocity and  a constant speed

	// get the direction to the new position
	Vector2 direction = Vector2::Normalize(position - this->position);
	
	// set the velocity to the direction multiplied by the speed
	velocity = direction * speed;
	
	// move the object with the velocity
	this->position += velocity * deltaTime;	
}

void RigidBody::MoveInDirection(Vector2 direction, float speed, float deltaTime)
{
	// move in a direction with velocity and a constant speed

	// set the velocity to the direction multiplied by the speed
	velocity = direction * speed;

	// move the object with the velocity
	this->position += velocity * deltaTime;
}

void RigidBody::Update(float deltaTime)
{
	if (!isEnabled) return;
	// Calculate acceleration
	acceleration.x = (force.x + friction.x) / mass;
	
	acceleration.y = gravity + (force.y / mass);

	// Calculate velocity
	
	velocity = acceleration * deltaTime;

	// Calculate position
	
	position = velocity;
}
