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
			collider = CollisionManager::RegisterNewCollider<GameObject, BoxCollider>(this, new BoxCollider(Vec2(transform->GetPosition().x, transform->GetPosition().y), Vec2(100, 100)));
			break;
		case 1:
			collider = CollisionManager::RegisterNewCollider<GameObject, CircleCollider>(this, new CircleCollider(Vec2(transform->GetPosition().x, transform->GetPosition().y), 50));
			break;
		case 2:
			collider = CollisionManager::RegisterNewCollider<GameObject, PolygonCollider>(this, new PolygonCollider(Vec2(transform->GetPosition().x, transform->GetPosition().y), PolygonShape::GetRandomPolygon(50)));
			break;
		default:break;
	}

	collider->AddOwnerAs<GameObject>(this);
	collider->AddListener(std::bind(&Enemy::OnCollisionEnter, this, std::placeholders::_1));

	moveSpeed = 100;

	direction = Direction::GetRandomDirection();
}

void Enemy::Update(float deltaTime)
{
	GameObject::Update(deltaTime);	
	collider->UpdatePosition(Vec2(transform->GetPosition().x, transform->GetPosition().y));
}

void Enemy::LateUpdate(float deltaTime)
{
	rigidBody->Update(deltaTime);
	rigidBody->MoveInDirection(direction, moveSpeed, deltaTime);
	transform->Translate(rigidBody->GetPosition());
}

void Enemy::OnCollisionEnter(Collision collision)
{
	GameObject* other = collision.GetColliderHit()->GetOwnerAs<GameObject>();

	if (!other->CompareTag(Tag::ENEMY))
	{
		color = other->GetColor();
	}

	Vector2 newDirection = Vector2 { collision.GetMinimumTranslationVector().GetX(), collision.GetMinimumTranslationVector().GetY() };
	direction = -newDirection.Normalized() * collision.GetImpulse();
}
