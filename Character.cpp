#include "Character.h"

Character::Character(Vector2 position) : GameObject(position)
{
	rigidBody = AddComponent<RigidBody>(new RigidBody);
	rigidBody->SetGravity(0);

	moveSpeed = 100;
}

Character::~Character()
{

}

void Character::Update(float deltatime)
{
	GameObject::Update(deltatime);
}