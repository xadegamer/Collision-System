#include "Collider.h"
#include "CollisionManager.h"

namespace CollisionSystem
{
	void Collider::AddColliderToManager()
	{
		CollisionManager::AddCollider(this);
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
