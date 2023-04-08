#include "Enemy.h"

#include  "Game.h"

#include "Engine.h"

Enemy::Enemy(Vector2 position) : Character(position)
{
	tag = Tag::ENEMY;
	
	rigidBody->SetPosition(transform->GetPosition());

	//collider = new BoxCollider { (GameObject*)this, transform->GetPosition(), Vector2(100, 100) };

	//collider = new CircleCollider { (GameObject*)this, transform->GetPosition(), 50 };

	std::vector<Vector2> points = { Vector2(50,50), Vector2(-20, 120), Vector2(50, 200), Vector2(200, 200), Vector2(200, 50) };

	collider = new PolygonCollider((GameObject*)this, transform->GetPosition(), points);

	collider->GetOnCollisionEnterEvent() = std::bind(&Enemy::OnCollisionEnter, this, std::placeholders::_1);

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
	GameObject* other = (GameObject*)collision.GetColliderHit()->GetOwner();
	if (other->CompareTag(Tag::PLAYER))
	{
		color = other->GetColor();
	}
}

bool Enemy::IsOutSideScreen()
{
	if (transform->GetPosition().x < 0 || transform->GetPosition().x > Engine::SCREEN_WIDTH || transform->GetPosition().y < 0 || transform->GetPosition().y > Engine::SCREEN_HEIGHT)
	{
		return true;
	}
	return false;
}
