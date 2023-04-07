#include "Enemy.h"

#include  "Game.h"

#include "Engine.h"

Enemy::Enemy(Vector2 position) : Character(position)
{
	tag = Tag::ENEMY;

	spriteRenderer->SetSortingOrder(SortingLayer::EnemyLayer);
	
	rigidBody->SetPosition(transform->GetPosition());

	collider = new BoxCollider;
	BoxCollider* boxCollider = static_cast<BoxCollider*>(collider);
	boxCollider->SetUp((GameObject*)this, transform->GetPosition(), Vector2(spriteRenderer->GetSprite()->textureWidth, spriteRenderer->GetSprite()->textureHeight));
	boxCollider->GetOnCollisionEnterEvent() = std::bind(&Enemy::OnCollisionEnter, this, std::placeholders::_1);

	//collider = new CircleCollider;
	//CircleCollider* circleCollider = static_cast<CircleCollider*>(collider);
	//circleCollider->SetUp(transform,transform->GetPosition(), spriteRenderer->GetSprite()->textureWidth / 2);
	//circleCollider->GetOnCollisionEnterEvent() = std::bind(&Enemy::OnCollisionEnter, this, std::placeholders::_1);

	//collider = new PolygonCollider;
	//PolygonCollider* polygonCollider = static_cast<PolygonCollider*>(collider);
	//std::vector<Vector2> points = { Vector2(0,0), Vector2(0, 100), Vector2(100, 100), Vector2(100,0) };
	//polygonCollider->SetUp((GameObject*)this, transform->GetPosition(), points);
	//polygonCollider->GetOnCollisionEnterEvent() = std::bind(&Enemy::OnCollisionEnter, this, std::placeholders::_1);
	
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
	
	collider->UpdatePosition(transform->GetPosition());

	PatrolState(deltaTime);
}

void Enemy::OnCollisionEnter(Collision collision)
{

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
		transform->SetRotation(MathUtility::GetAngleFromTraget(transform->GetPosition() - collider->GetCenter(), currentPatrolPoint - transform->GetPosition(), spriteRenderer->GetSprite()->textureHeight, spriteRenderer->GetSprite()->textureWidth));
		rigidBody->MoveToPosition(currentPatrolPoint, 100, deltaTime);
		transform->SetPosition(rigidBody->GetPosition());
	}
}