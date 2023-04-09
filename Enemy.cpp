#include "Enemy.h"

#include <stdlib.h>

#include  "Game.h"

#include "Engine.h"

#include "PolygonShape.h"

#include "Direction.h"

Enemy::Enemy(Vector2 position) : GameObject(position)
{
	tag = Tag::ENEMY;
	
	rigidBody = AddComponent<RigidBody>(new RigidBody);

	rigidBody->SetGravity(0);

	rigidBody->SetPosition(transform->GetPosition());

	// Random collider type
	int random = rand() % 3;

	switch (random)
	{
		case 0:
			collider = new BoxCollider{ (GameObject*)this, transform->GetPosition(), Vector2(100, 100) };
			break;
		case 1:
			collider = new CircleCollider{ (GameObject*)this, transform->GetPosition(), 50 };
			break;
		case 2:
			collider = new PolygonCollider((GameObject*)this, transform->GetPosition(), PolygonShape::GetRandomPolygon(50));
			break;
		default:break;
	}

	collider->AddListener(std::bind(&Enemy::OnCollisionEnter, this, std::placeholders::_1));

	moveSpeed = 100;

	direction = Direction::GetRandomDirection();
}

void Enemy::Update(float deltaTime)
{
	GameObject::Update(deltaTime);	
	collider->UpdatePosition(transform->GetPosition());
}

void Enemy::LateUpdate(float deltaTime)
{
	rigidBody->Update(deltaTime);
	rigidBody->MoveInDirection(direction, moveSpeed, deltaTime);
	transform->Translate(rigidBody->GetPosition());
}

void Enemy::OnCollisionEnter(Collision collision)
{
	GameObject* other = (GameObject*)collision.GetColliderHit()->GetOwner();

	if (!other->CompareTag(Tag::ENEMY))
	{
		color = other->GetColor();
	}

	direction = -collision.GetMinimumTranslationVector().Normalized() * collision.GetImpulse();
}
