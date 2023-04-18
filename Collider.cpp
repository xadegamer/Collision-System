#include "Collider.h"

#include "CollisionManager.h"

namespace CollisionSystem
{
	std::vector<Collider*> Collider::_allColliders = std::vector<Collider*>();

	Collider::Collider(void* owner, Vec2 nextPosition, bool isStatic)
	{
		_currentCollidedObject = nullptr;
		_isEnabled = true;

		CollisionManager::AddCollider(this);

		this->_owner = owner;
		this->_isStatic = isStatic;
	}

	void Collider::OnCollision()
	{
		if (_collision.GetColliderHit() == nullptr || !_isEnabled) return;

		if (_OnCollisionEnterEvent != nullptr) _OnCollisionEnterEvent(_collision);
	}

	void Collider::SetCollisionProperty(Collider* colliderHit, Vec2 minimumTranslationVector, float impulse)
	{
		_collision = { colliderHit , minimumTranslationVector , impulse };
	}

	void Collider::AddListener(std::function<void(Collision other)> OnCollisionEnterEvent)
	{
		this->_OnCollisionEnterEvent = OnCollisionEnterEvent;
	}
}
