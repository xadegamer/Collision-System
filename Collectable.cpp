#include "Collectable.h"

Collectable::Collectable(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, float amount) : Prop(position, spriteName, colliderType, sortingOrder, true, true)
{
	SetTag(Tag::COLLECTABLE);
	this->amount = amount;
	collider->GetOnCollisionEnterEvent() = std::bind(&Collectable::OnCollisionEnter, this, std::placeholders::_1);
}

Collectable::~Collectable()
{
}

void Collectable::Update(float deltaTime)
{
	Prop::Update(deltaTime);
}

void Collectable::OnCollisionEnter(Collider* other)
{
	if (other->GetGameObject()->CompareTag(Tag::PLAYER))
	{
		Player* player = dynamic_cast<Player*>(other->GetGameObject());
		if (player)	PickUp(player);
	}
}

void Collectable::PickUp(Player* player)
{
	GameObject::Destroy(this);
}