#include "Collider.h"

std::vector<Collider*> Collider::allColliders = std::vector<Collider*>();

Collider::Collider()
{
	currentCollidedObject = nullptr;
	allColliders.push_back(this);
	isEnabled = true;
}

Collider::~Collider()
{
	for (int i = 0; i < allColliders.size(); i++)
	{
		if (allColliders[i] == this)
		{
			allColliders.erase(allColliders.begin() + i);
			break;
		}
	}
}

void Collider::SetUp(void* owner, Vector2 nextPosition, bool isStatic)
{
	this->owner = owner;
	this->isStatic = isStatic;
	UpdatePosition(nextPosition);
}

void Collider::OnCollision()
{
	if (collision.GetColliderHit() == nullptr || !isEnabled) return;
	
	if (OnCollisionEnterEvent != nullptr) OnCollisionEnterEvent(collision);
}

void Collider::SetCollisionProperty(Collider* colliderHit, Vector2 minimumTranslationVector, float impulse)
{
	collision.SetColliderHit(colliderHit);
	collision.SetMinimumTranslationVector(minimumTranslationVector);
	collision.SetImpulse(impulse);
}
