#include "Enemy.h"

#include <stdlib.h>

#include  "Game.h"

#include "Engine.h"

#include "PolygonShape.h"

#include "Direction.h"

Enemy::Enemy(Vector2 position) : Character(position)
{
	tag = Tag::ENEMY;
	
	rigidBody->SetPosition(transform->GetPosition());

	// random collider type
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

	collider->GetOnCollisionEnterEvent() = std::bind(&Enemy::OnCollisionEnter, this, std::placeholders::_1);

	spawnPoint = transform->GetPosition();
	
	currentPatrolPoint = MathUtility::RandomPositionAroundRange(spawnPoint, 300);

	moveSpeed = 100;

	direction = Direction::GetRandomDirection();
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
	Character::Update(deltaTime);	

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
