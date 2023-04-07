#include "Enemy.h"

#include  "Game.h"

#include "Engine.h"

Enemy::Enemy(Vector2 position) : Character(position)
{
	tag = Tag::ENEMY;

	spriteRenderer->SetSortingOrder(SortingLayer::EnemyLayer);
	
	rigidBody->SetPosition(transform->GetPosition());

	//collider = new BoxCollider;
	//BoxCollider* boxCollider = static_cast<BoxCollider*>(collider);
	//boxCollider->SetUp((GameObject*)this, transform->GetPosition(), Vector2(spriteRenderer->GetSprite()->textureWidth, spriteRenderer->GetSprite()->textureHeight));
	//boxCollider->GetOnCollisionEnterEvent() = std::bind(&Enemy::OnCollisionEnter, this, std::placeholders::_1);

	//collider = new CircleCollider;
	//CircleCollider* circleCollider = static_cast<CircleCollider*>(collider);
	//circleCollider->SetUp(transform,transform->GetPosition(), spriteRenderer->GetSprite()->textureWidth / 2);
	//circleCollider->GetOnCollisionEnterEvent() = std::bind(&Enemy::OnCollisionEnter, this, std::placeholders::_1);

	collider = new PolygonCollider;
	PolygonCollider* polygonCollider = static_cast<PolygonCollider*>(collider);
		std::vector<Vector2> points = { Vector2(50,50), Vector2(-20, 120), Vector2(50, 200), Vector2(200, 200), Vector2(200, 50) };
	polygonCollider->SetUp((GameObject*)this, transform->GetPosition(), points);
	polygonCollider->GetOnCollisionEnterEvent() = std::bind(&Enemy::OnCollisionEnter, this, std::placeholders::_1);
	
	spawnPoint = transform->GetPosition();
	
	currentPatrolPoint = MathUtility::RandomPositionAroundRange(spawnPoint, 300);

	moveSpeed = 100;

	direction = Vector2(1, 0);
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
	Character::Update(deltaTime);	

	collider->UpdatePosition(transform->GetPosition());

	if (IsOutSideScreen())
	{
		direction * -1;
	}
}

void Enemy::LateUpdate(float deltaTime)
{
	rigidBody->Update(deltaTime);
	rigidBody->MoveInDirection(direction, moveSpeed, deltaTime);
	transform->Translate(rigidBody->GetPosition());
}

void Enemy::OnCollisionEnter(Collision collision)
{
	direction = -collision.GetMinimumTranslationVector().Normalized();
}

bool Enemy::IsOutSideScreen()
{
	if (transform->GetPosition().x < 0 || transform->GetPosition().x > Engine::SCREEN_WIDTH || transform->GetPosition().y < 0 || transform->GetPosition().y > Engine::SCREEN_HEIGHT)
	{
		return true;
	}
	return false;
}
