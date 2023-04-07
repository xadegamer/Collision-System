#pragma once 

#include "Component.h"
#include "Vector2.h"

#include <iostream>

class RigidBody : public Component
{
	
private:

	float gravity;
	Vector2 position;
	Vector2 velocity;
	float mass;
	Vector2 force;
	Vector2 friction;
	Vector2 acceleration;
	
public:
	RigidBody();
	~RigidBody();

	// Setters for gravity and mass
	inline void SetMass(float mass) { this->mass = mass; }
	inline void SetGravity(float gravity) { this->gravity = gravity; }

	// Force
	inline void ApplyForce(Vector2 force) { this->force = force; }
	inline void ApplyForceX(float x) {this->force.x = x;}
	inline void ApplyForceY(float y) {this->force.y = y;}
	
	inline void ResetForce() { this->force = Vector2(0, 0); }
	inline void ResetForceX() { this->force.x = 0; }
	inline void ResetForceY() { this->force.y = 0; }

	void MoveToPosition(Vector2 position, float speed, float deltaTime);

	void MoveInDirection (Vector2 direction, float speed, float deltaTime);
	
	//Friction
	inline void ApplyFriction(Vector2 friction) { this->friction = friction; }
	inline void ResetFriction() { this->friction = Vector2(0, 0); }

	// Velocity
	inline void SetVelocity(Vector2 velocity) { this->velocity = velocity; }
	inline void SetVelocityX(float x) { this->velocity.x = x; }
	inline void SetVelocityY(float y) { this->velocity.y = y; }

	//Position
	inline void SetPosition(Vector2 position) { this->position = position; }

	// Getters
	inline float GetMass() { return  mass; }
	inline Vector2 GetPosition() { return position; }
	inline Vector2 GetVelocity() { return velocity; }
	inline Vector2 GetAcceleration() { return acceleration; }
	
	void Update(float deltaTime);
};

