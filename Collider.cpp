#include "Collider.h"

// init static 	static std::vector<GameObject*> activeGameobjects;
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

void Collider::OnCollision(Collider* other)
{
	if (other == nullptr || !isEnabled) return;
	
	if (OnCollisionEnterEvent != nullptr) OnCollisionEnterEvent(other);
}