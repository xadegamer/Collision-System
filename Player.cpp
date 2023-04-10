#include "Player.h"

#include  "Game.h"

#include "Engine.h"

#include "PolygonShape.h"

Player::Player(Vector2 position) : GameObject(position)
{
	color = Color::GetColor(ColorType::Yellow);

	tag = Tag::PLAYER;

	rigidBody = AddComponent<RigidBody>(new RigidBody);

	rigidBody->SetGravity(0);

	rigidBody->SetPosition(transform->GetPosition());

	collider = new CircleCollider { (GameObject*)this, Vec2(transform->GetPosition().x, transform->GetPosition().y), 50};

	collider->AddListener(std::bind(&Player::OnCollisionEnter, this, std::placeholders::_1));

	moveSpeed = 100;

	runSpeed = 200;

	currentMoveSpeed = moveSpeed;
}

void Player::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	rigidBody->ResetForce();

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
	
	collider->UpdatePosition(Vec2(transform->GetPosition().x, transform->GetPosition().y));
	
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
