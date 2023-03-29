#include "Collider.h"

Collider::Collider()
{
	currentCollidedObject = nullptr;
	colliderRect = new SDL_Rect();
}

Collider::~Collider()
{
	colliderRect = nullptr;
}

void Collider::someFunc()
{
}

void Collider::SetUp(Transform* owner, Vector2 size, bool isStatic)
{
	this->owner = owner;
	this->isStatic = isStatic;
	
	colliderRect->w = size.x;
	colliderRect->h = size.y;
	colliderRect->x = owner->GetPosition().x;
	colliderRect->y = owner->GetPosition().y;
}	

void Collider::OnCollision(Collider* other)
{
	if (other == nullptr || !isEnabled) return;
	
	if (OnCollisionEnterEvent != nullptr) OnCollisionEnterEvent(other);
}

Vector2 Collider::GetCentre()
{
	return Vector2(colliderRect->x + colliderRect->w / 2, colliderRect->y + colliderRect->h / 2);
}
