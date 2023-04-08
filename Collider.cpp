#include "Collider.h"

std::vector<Collider*> Collider::allColliders = std::vector<Collider*>();

Collider::Collider(void* owner, Vector2 nextPosition, bool isStatic)
{
	currentCollidedObject = nullptr;
	allColliders.push_back(this);
	isEnabled = true;

	this->owner = owner;
	this->isStatic = isStatic;
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
