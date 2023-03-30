#include "Player.h"

#include  "Game.h"

#include "Engine.h"

Player::Player(Vector2 position) : Character(position)
{
	tag = Tag::PLAYER;

	spriteRenderer->SetSortingOrder(SortingLayer::PlayerLayer);

	boxCollider = new BoxCollider;
	boxCollider->SetUp(transform, Vector2(spriteRenderer->GetSprite()->textureWidth, spriteRenderer->GetSprite()->textureHeight));
	boxCollider->GetOnCollisionEnterEvent() = std::bind(&Player::OnCollisionEnter, this, std::placeholders::_1);

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

	transform->SetRotation(MathUtility::GetAngleFromMouse(transform->GetPosition(), spriteRenderer->GetSprite()->textureHeight, spriteRenderer->GetSprite()->textureWidth) );

	//clamp player position to level bound with scale
	transform->SetXPosition(MathUtility::Clamp(transform->GetPosition().x, 0 - (spriteRenderer->GetSprite()->textureWidth / 2), Engine::SCREEN_WIDTH - (spriteRenderer->GetSprite()->textureWidth)) );
	transform->SetYPosition(MathUtility::Clamp(transform->GetPosition().y, 0 - (spriteRenderer->GetSprite()->textureHeight / 2), Engine::SCREEN_HEIGHT - (spriteRenderer->GetSprite()->textureHeight)) );

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
	
	boxCollider->Update();
	
	GameObject::Update(deltaTime);
}

void Player::LateUpdate(float deltaTime)
{
	rigidBody->Update(deltaTime);
	transform->Translate(rigidBody->GetPosition());
}

void Player::OnCollisionEnter(Collider* other)
{
	std:: cout << "Player collided with " << other->GetOwner()->GetGameObject()->GetTag()<< std::endl;
	//if (!other->IsTrigger())
	//{
	//	Vector2 direction = transform->GetPosition() - other->GetGameObject()->GetTransform()->GetPosition();
	//	direction.normalize();
	//	transform->SetPosition(transform->GetPosition() += direction * 1.8);
	//}
}
