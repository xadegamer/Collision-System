#include "Player.h"

#include  "Game.h"

#include "Engine.h"

Player::Player(Vector2 position) : Character(position)
{
	tag = Tag::PLAYER;

//	collider = new BoxCollider { (GameObject*)this, transform->GetPosition(), Vector2(100, 100) };

	collider = new CircleCollider { (GameObject*)this, transform->GetPosition(), 50 };

	//std::vector<Vector2> points = { Vector2(0,0), Vector2(0, 100), Vector2(100, 100), Vector2(100,0) };
	//collider = new PolygonCollider ((GameObject*)this, transform->GetPosition(), points);

	collider->GetOnCollisionEnterEvent() = std::bind(&Player::OnCollisionEnter, this, std::placeholders::_1);

	currentMoveSpeed = moveSpeed;

	runSpeed = 200;
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
	Character::Update(deltaTime);

	rigidBody->ResetForce();

	//clamp player position to level bound with scale
	transform->SetXPosition(MathUtility::Clamp(transform->GetPosition().x, 0 , Engine::SCREEN_WIDTH));
	transform->SetYPosition(MathUtility::Clamp(transform->GetPosition().y, 0, Engine::SCREEN_HEIGHT));

	if (!canMove) return;

	if (InputManager::GetKey(SDL_SCANCODE_W))
	{
		rigidBody->ApplyForceY(-currentMoveSpeed);
	}

	if (InputManager::GetKey(SDL_SCANCODE_S))
	{
		rigidBody->ApplyForceY(currentMoveSpeed);
	}

	if (InputManager::GetKey(SDL_SCANCODE_A))
	{
		rigidBody->ApplyForceX(-currentMoveSpeed);
	}

	if (InputManager::GetKey(SDL_SCANCODE_D))
	{
		rigidBody->ApplyForceX(currentMoveSpeed);
	}

	// if hold shift, increase move speed
	currentMoveSpeed = InputManager::GetKey(SDL_SCANCODE_LSHIFT) ? runSpeed : moveSpeed;
	
	collider->UpdatePosition(transform->GetPosition());
	
	GameObject::Update(deltaTime);
}

void Player::LateUpdate(float deltaTime)
{
	rigidBody->Update(deltaTime);
	transform->Translate(rigidBody->GetPosition());
}

void Player::OnCollisionEnter(Collision collision)
{
	GameObject* collided = (GameObject*)collision.GetColliderHit()->GetOwner();
}
