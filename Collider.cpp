#include "Collider.h"

// init static 	static std::vector<GameObject*> activeGameobjects;
std::vector<Collider*> Collider::allColliders = std::vector<Collider*>();

Collider::Collider()
{
	currentCollidedObject = nullptr;
	colliderRect = new SDL_Rect();
	allColliders.push_back(this);
	isEnabled = true;
}

Collider::~Collider()
{
	colliderRect = nullptr;

	for (int i = 0; i < allColliders.size(); i++)
	{
		if (allColliders[i] == this)
		{
			allColliders.erase(allColliders.begin() + i);
			break;
		}
	}

	delete colliderRect;
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
