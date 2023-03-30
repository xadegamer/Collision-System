#include "Character.h"

Character::Character(Vector2 position) : GameObject(position)
{
	spriteRenderer = AddComponent<SpriteRenderer>(new SpriteRenderer);
	rigidBody = AddComponent<RigidBody>(new RigidBody);
	rigidBody->SetGravity(0);

	moveSpeed = 100;

	// to remove
	spriteRenderer->SetSprite(AssetManager::GetSprite("BarrelSmall"));
}

Character::~Character()
{

}

void Character::Update(float deltatime)
{
	GameObject::Update(deltatime);
}

void Character::Draw()
{
	spriteRenderer->Draw(transform->GetPosition(), transform->GetRotation());
}