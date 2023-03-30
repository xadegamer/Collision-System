#include "Enemy.h"

#include  "Game.h"

#include "Engine.h"

Enemy::Enemy(Vector2 position) : Character(position)
{
	tag = Tag::ENEMY;

	spriteRenderer->SetSortingOrder(SortingLayer::EnemyLayer);
	
	rigidBody->SetPosition(transform->GetPosition());

	circleCollider = new CircleCollider;
	circleCollider->SetUp(transform, spriteRenderer->GetSprite()->textureWidth / 2, 1);
	circleCollider->GetOnCollisionEnterEvent() = std::bind(&Character::OnCollisionEnter, this, std::placeholders::_1);
	
	spawnPoint = transform->GetPosition();
	
	currentPatrolPoint = MathUtility::RandomPositionAroundRange(spawnPoint, 300);
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
	Character::Update(deltaTime);
	
	if (!canMove) return;
	
	circleCollider->Update();

	//PatrolState(deltaTime);
}

void Enemy::OnCollisionEnter(Collider* other)
{
	//if (other->GetGameObject()->CompareTag(Tag::ENEMY))
	//{
	//	Vector2 direction = transform->GetPosition() - other->GetGameObject()->GetTransform()->GetPosition();
	//	direction.normalize();
	//	transform->SetPosition(transform->GetPosition() += direction * 1.5);
	//}
}


void Enemy::PatrolState(float deltaTime)
{
	if (MathUtility::DistanceBetweenTwoPoints(transform->GetPosition(), currentPatrolPoint) <= 5)
	{
		rigidBody->SetVelocity(Vector2(0, 0));
		currentPatrolPoint = MathUtility::RandomPositionAroundRange(spawnPoint, 300);
	}
	else
	{
		transform->SetRotation(MathUtility::GetAngleFromTraget(transform->GetPosition() - circleCollider->GetCentre(), currentPatrolPoint - transform->GetPosition(), spriteRenderer->GetSprite()->textureHeight, spriteRenderer->GetSprite()->textureWidth));
		rigidBody->MoveToPosition(currentPatrolPoint, 100, deltaTime);
		transform->SetPosition(rigidBody->GetPosition());
	}
}